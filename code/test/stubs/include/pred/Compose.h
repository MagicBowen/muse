#ifndef H942BC4AF_B66C_437E_8834_7D2220FAF1F9
#define H942BC4AF_B66C_437E_8834_7D2220FAF1F9

#include <muse/muse.h>
#include <tuple>

MUSE_NS_BEGIN

template<typename ... Fs>
struct Compose
{
    Compose(Fs&& ... fs) : functions(std::forward<Fs>(fs) ...) {}

    template<size_t N, typename ... Ts>
    auto apply(std::integral_constant<size_t, N>, Ts&& ... ts) const
    {
        return apply( std::integral_constant<size_t, N - 1>{}
                    , std::get<N>(functions)(std::forward<Ts>(ts)...));
    }

    template<typename ... Ts>
    auto apply(std::integral_constant<size_t, 0>, Ts&& ... ts) const
    {
        return std::get<0>(functions)(std::forward<Ts>(ts)...);
    }

    template<typename ... Ts>
    auto operator()(Ts&& ... ts) const
    {
        return apply(std::integral_constant<size_t, sizeof ... (Fs) - 1>{}, std::forward<Ts>(ts) ...);
    }

    std::tuple<Fs ...> functions;
};

template<typename ... Fs>
auto make_compose(Fs&& ... fs)
{
    return Compose<std::decay_t<Fs> ...>(std::forward<Fs>(fs) ...);
}

MUSE_NS_END

#endif
