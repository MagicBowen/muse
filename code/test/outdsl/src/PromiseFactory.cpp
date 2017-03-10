#include <outdsl/include/PromiseFactory.h>
#include <rapidjson/document.h>
#include <string>
#include <muse/base/log.h>
#include <muse/pred/Compose.h>
#include <muse/pred/PredAdaper.h>
#include <muse/fact/ClosureFact.h>
#include <muse/promise/ConcurrentPromise.h>
#include <muse/promise/SequentialPromise.h>
#include <muse/promise/OptionalPromise.h>
#include <muse/promise/UntilPromise.h>
#include <muse/promise/DaemonPromise.h>
#include <muse/promise/ExistPromise.h>
#include <muse/promise/NotExistPromise.h>
#include <fakefact/include/fact/Collision.h>
#include <fakefact/include/fact/Stop.h>
#include <fakefact/include/fact/Distance.h>
#include <fakefact/include/fact/Duration.h>
#include <fakefact/include/pred/GreaterThan.h>
#include <fakefact/include/pred/LessThan.h>
#include <fakefact/include/pred/EqualTo.h>
#include <fakefact/include/pred/Between.h>
#include <fakefact/include/algo/Average.h>
#include <fakefact/include/algo/Variance.h>
#include <fakefact/include/fact/DistanceTo.h>

using namespace rapidjson;

MUSE_NS_BEGIN

namespace
{
    Promise* createPromise(const Value&);

    bool isPromise(const Value& json, const char* name)
    {
        return json["type"].GetString() == std::string(name);
    }

    bool isFact(const Value& json, const char* name)
    {
        return json["name"].GetString() == std::string(name);
    }

    bool isPred(const Value& json, const char* name)
    {
        return json["name"].GetString() == std::string(name);
    }

    bool isAlgo(const char* algo, const char* expect)
    {
        return std::string(algo) == std::string(expect);
    }

    template<typename ALGO, typename PRED_PARAM, typename PRED>
    Pred<PRED_PARAM>* createComposePred(PRED* pred)
    {
        auto algo = new ALGO();
        auto composed = new Compose<ALGO, PRED>(*algo, *pred);
        return new PredAdapter<Compose<ALGO, PRED>, PRED_PARAM>(*composed);
    }

    template<typename PRED_PARAM, typename PRED>
    Pred<PRED_PARAM>* createAlgoPred(PRED* pred, const char* algo)
    {
        if(algo == nullptr) return new PredAdapter<PRED, PRED_PARAM>(*pred);
        if(isAlgo(algo, "average")) return createComposePred<Average<PRED_PARAM>, PRED_PARAM>(pred);
        if(isAlgo(algo, "variance")) return createComposePred<Variance<PRED_PARAM>, PRED_PARAM>(pred);

        ERR_LOG("json has no matched algo name");
        return nullptr;
    }

    template<typename PRED, typename PRED_PARAM>
    Pred<PRED_PARAM>* create1ParamPred(const Value& json, const char* algo)
    {
        auto pred = new PRED(PRED_PARAM(json["param"].GetDouble()));
        return createAlgoPred<PRED_PARAM>(pred, algo);
    }

    template<typename PRED, typename PRED_PARAM>
    Pred<PRED_PARAM>* create2ParamPred(const Value& json, const char* algo)
    {
        auto pred = new PRED( PRED_PARAM(json["param"][0].GetDouble())
                            , PRED_PARAM(json["param"][1].GetDouble()));
        return createAlgoPred<PRED_PARAM>(pred, algo);
    }

    template<typename PRED_PARAM>
    Pred<PRED_PARAM>* createEqualToPred(const Value& json, const char* algo)
    {
        return create1ParamPred<EqualTo<PRED_PARAM>, PRED_PARAM>(json, algo);
    }

    template<typename PRED_PARAM>
    Pred<PRED_PARAM>* createLessThanPred(const Value& json, const char* algo)
    {
        return create1ParamPred<LessThan<PRED_PARAM>, PRED_PARAM>(json, algo);
    }

    template<typename PRED_PARAM>
    Pred<PRED_PARAM>* createGreaterThanPred(const Value& json, const char* algo)
    {
        return create1ParamPred<GreaterThan<PRED_PARAM>, PRED_PARAM>(json, algo);
    }

    template<typename PRED_PARAM>
    Pred<PRED_PARAM>* createBwtweenPred(const Value& json, const char* algo)
    {
        return create2ParamPred<Between<PRED_PARAM>, PRED_PARAM>(json, algo);
    }

    template<typename PRED_PARAM>
    Pred<PRED_PARAM>* createPred(const Value& json, const char* algo)
    {
        if(!json.HasMember("name"))
        {
            ERR_LOG("json has no pred name");
            return nullptr;
        }

        if(isPred(json, "equalto"))     return createEqualToPred<PRED_PARAM>(json, algo);
        if(isPred(json, "lessthan"))    return createLessThanPred<PRED_PARAM>(json, algo);
        if(isPred(json, "greaterthan")) return createGreaterThanPred<PRED_PARAM>(json, algo);
        if(isPred(json, "between"))     return createBwtweenPred<PRED_PARAM>(json, algo);

        ERR_LOG("json has no matched pred name");
        return nullptr;
    }

    Fact* createCollisionFact(const Value& json)
    {
        return new Collision();
    }

    Fact* createStopFact(const Value& json)
    {
        return new Stop();
    }

    template<typename FACT>
    FACT* createConcreteFact(const Value& json)
    {
        return new FACT();
    }

    template<typename FACT>
    FACT* createConcreteParamFact(const Value& json)
    {
        if(!json.HasMember("param"))
        {
            ERR_LOG("Fact lost construction parameter");
            return nullptr;
        }
        return new FACT(typename  FACT::PredArgType (json["param"].GetDouble()));
    }

    template<typename FACT>
    Fact* addPredForFact(const Value& json, FACT* fact)
    {
        const char* algo = json.HasMember("algo") ? json["algo"].GetString() : nullptr;
        auto pred = createPred<typename FACT::PredArgType>(json["pred"], algo);
        fact->addPred(*pred);
        return fact;
    }

    template<typename FACT>
    Fact* createPredFactWithoutParam(const Value& json)
    {
        FACT* fact = createConcreteFact<FACT>(json);
        return addPredForFact(json, fact);
    }

    template<typename FACT>
    Fact* createPredFactWithParam(const Value& json)
    {
        FACT* fact = createConcreteParamFact<FACT>(json);
        return addPredForFact(json, fact);
    }

    Fact* createDurationFact(const Value& json)
    {
        return createPredFactWithoutParam<Duration>(json);
    }

    Fact* createDistanceFact(const Value& json)
    {
        return createPredFactWithoutParam<Distance>(json);
    }

    Fact* createDistanceToFact(const Value& json)
    {
        return createPredFactWithParam<DistanceTo>(json);
    }

    Fact* createFact(const Value& json)
    {
        if(!json.HasMember("name"))
        {
            ERR_LOG("json has no fact name");
            return nullptr;
        }

        Fact* fact = nullptr;
        if(isFact(json, "collision"))       fact = createCollisionFact(json);
        else if(isFact(json, "stop"))       fact = createStopFact(json);
        else if(isFact(json, "duration"))   fact = createDurationFact(json);
        else if(isFact(json, "distance"))   fact = createDistanceFact(json);
        else if(isFact(json, "distanceto")) fact = createDistanceToFact(json);
        else
        {
            ERR_LOG("json has no matched fact name");
            return nullptr;
        }

        if(json.HasMember("closure") && json["closure"].GetBool())
        {
            return new ClosureFact(*fact);
        }
        return fact;
    }

    template<typename PROMISE>
    Promise* createBasePromise(const Value& json)
    {
        if(!json.HasMember("fact"))
        {
            ERR_LOG("json has no matched fact obejct");
            return nullptr;
        }
        Fact* fact = createFact(json["fact"]);
        return new PROMISE(*fact);
    }

    Promise* createExistPromise(const Value& json)
    {
        return createBasePromise<ExistPromise>(json);
    }

    Promise* createNotExistPromise(const Value& json)
    {
        return createBasePromise<NotExistPromise>(json);
    }

    template<typename PROMISE>
    Promise* createDecoratePromise(const Value& json)
    {
        const Value& value = json["promises"];
        Promise* p0 = createPromise(value[0]);
        Promise* p1 = createPromise(value[1]);
        DecoratorPromise* promise = new PROMISE(*p0, *p1);
        return promise;
    }

    Promise* createDaemonPromise(const Value& json)
    {
        return createDecoratePromise<DaemonPromise>(json);
    }

    Promise* createUntilPromise(const Value& json)
    {
        return createDecoratePromise<UntilPromise>(json);
    }

    template<typename PROMISE>
    Promise* createCompositePromise(const Value& json)
    {
        const Value& value = json["promises"];
        CompositePromise* promise = new PROMISE();
        for(SizeType i = 0; i < value.Size(); i++)
        {
            auto p = createPromise(value[i]);
            promise->addPromise(*p);
        }
        return promise;
    }

    Promise* createConcurrentPromise(const Value& json)
    {
        return createCompositePromise<ConcurrentPromise>(json);
    }

    Promise* createSequentialPromise(const Value& json)
    {
        return createCompositePromise<SequentialPromise>(json);
    }

    Promise* createOptionalPromise(const Value& json)
    {
        return createCompositePromise<OptionalPromise>(json);
    }

    Promise* createPromise(const Value& json)
    {
        if(!json.HasMember("type"))
        {
            ERR_LOG("json has no promise type");
            return nullptr;
        }

        if(isPromise(json, "concurrent")) return createConcurrentPromise(json);
        if(isPromise(json, "sequential")) return createSequentialPromise(json);
        if(isPromise(json, "optional")) return createOptionalPromise(json);
        if(isPromise(json, "until")) return createUntilPromise(json);
        if(isPromise(json, "daemon")) return createDaemonPromise(json);
        if(isPromise(json, "exist")) return createExistPromise(json);
        if(isPromise(json, "notexist")) return createNotExistPromise(json);

        ERR_LOG("json has no matched promise name");
        return nullptr;
    }
}

Promise* PromiseFactory::create(const char* json)
{
    Document document;
    document.Parse(json);

    if(!document.IsObject())
    {
        ERR_LOG("json format error");
        return nullptr;
    }

    return createPromise(document);
}

MUSE_NS_END
