import unittest
import json
from SyntaxTranslator import parse_to_json



class TestSyntaxTranslator(unittest.TestCase):
    def setUp(self):
        pass

    def debug(self, json_str):
        temp = json.loads(json_str)
        print(json.dumps(temp, indent = 4))


    def assert_json(self, input, expect):
        result = parse_to_json(input)
        self.assertEqual(json.loads(expect), json.loads(result))


    def test_empty_input(self):
        self.assertEqual(parse_to_json(''), '')


    def test_no_promise(self):
        self.assertRaises(SyntaxError, parse_to_json('F1: collision.'))


    def test_no_end_symbol(self):
        self.assertRaises(SyntaxError, parse_to_json('promise: collision'))


    def test_exist_promise(self):
        input = '''promise : collision.'''
        expect = '''{"type": "exist", "fact": {"name": "collision"}}'''
        self.assert_json(input, expect)


    def test_notexist_promise(self):
        input = '''promise : !collision.'''
        expect = '''{"type": "notexist", "fact": {"name": "collision"}}'''
        self.assert_json(input, expect)


    def test_concurrent_promise(self):
        input = '''promise : collision && stop.'''
        expect = '''{"type" : "concurrent",
                     "promises" : [ {"type": "exist", "fact": {"name": "collision"}},
                                    {"type": "exist", "fact": {"name": "stop"}}
                                  ]
                    }'''
        self.assert_json(input, expect)


    def test_sequential_promise(self):
        input = '''promise : collision -> stop.'''
        expect = '''{"type" : "sequential",
                     "promises" : [ {"type": "exist", "fact": {"name": "collision"}},
                                    {"type": "exist", "fact": {"name": "stop"}}
                                  ]
                    }'''
        self.assert_json(input, expect)


    def test_until_promise(self):
        input = '''promise : collision -| stop.'''
        expect = '''{"type" : "until",
                     "promises" : [ {"type": "exist", "fact": {"name": "collision"}},
                                    {"type": "exist", "fact": {"name": "stop"}}
                                  ]
                    }'''
        self.assert_json(input, expect)


    def test_composite_promise(self):
        input = '''promise : collision -> (stop && collision).'''
        expect = '''{ "type" : "sequential",
                      "promises" : [ {"type": "exist", "fact": {"name": "collision"}},
                                     {"type" : "concurrent",
                                      "promises" : [ {"type": "exist", "fact": {"name": "stop"}},
                                                     {"type": "exist", "fact": {"name": "collision"}}
                                                   ]
                                      }
                                    ]
                    }'''
        self.assert_json(input, expect)


    def test_duplicate_fact(self):
        self.assertRaises(SyntaxError, parse_to_json('f1: collision. f1: stop. promise: stop.'))   


    def test_reference_undefined_fact(self):
        self.assertRaises(SyntaxError, parse_to_json('f1: collision. promise: f2.'))   


    def test_reference_fact(self):
        input = ''' f1 : collision.
                    promise : f1.'''

        expect = '''{"type": "exist", "fact": {"name": "collision"}}'''

        self.assert_json(input, expect)


    def test_reference_closure_fact(self):
        input = ''' f1 : collision.
                    promise : [f1].'''

        expect = '''{"type": "exist", "fact": {"name": "collision", "closure": true}}'''

        self.assert_json(input, expect)


    def test_reference_fact_with_predicate(self):
        input = ''' f1 : duration predicate that equal to 5 s.
                    promise : f1.'''

        expect = '''{"type": "exist", "fact": {"name": "duration", "pred" : {"name" : "equalto", "param" : 5}}}'''

        self.assert_json(input, expect)


    def test_reference_fact_with_algo(self):
        input = ''' f1 : duration predicate that average equal to 5 s.
                    promise : f1.'''

        expect = '''{"type": "exist", "fact": {"name": "duration", "algo" : "average", "pred" : {"name" : "equalto", "param" : 5}}}'''

        self.assert_json(input, expect)
        

    def test_reference_fact_with_algo(self):
        input = ''' f1 : duration predicate that average equal to 5 s.
                    promise : f1.'''

        expect = '''{"type": "exist", "fact": {"name": "duration", "algo" : "average", "pred" : {"name" : "equalto", "param" : 5}}}'''

        self.assert_json(input, expect)


    def test_reference_distance_to_fact(self):
        input = ''' f1 : distance to vehicle 2 predicate that less than 10.
                    promise : f1.'''

        expect = '''{"type": "exist", "fact": {"name": "distance", "param" : 2, "pred" : {"name" : "lessthan", "param" : 10}}}'''

        self.assert_json(input, expect)


    def test_reference_fact_with_between_predicate(self):
        input = ''' f1 : distance to vehicle 2 predicate that between 4 m and 10 m.
                    promise : f1.'''

        expect = '''{"type": "exist", "fact": {"name": "distance", "param" : 2, "pred" : {"name" : "between", "param" : [4, 10]}}}'''

        self.assert_json(input, expect)


    def test_complex_composite_promise(self):
        input = ''' f1 : distance to vehicle 2 predicate that average between 4 m and 10 m.
                    f2 : lane gap predicate that variance greater than 1.5.
                    f3 : lane change predicate that equal to 3.
                    f4 : stop.
                    promise : !collision -< (f3 -> ([f1] && [f2]) -| f4).'''

        expect = '''{ "type"     : "daemon",
                      "promises" : [ { "type" : "until",
                                       "promises" : [ { "type" : "sequential" , "promises" : [ { "type" : "exist" , "fact" : {"name" : "lanechange", "pred" : {"name" : "equalto", "param" : 3}}},
                                                                                               { "type" : "concurrent", "promises" : [ { "type" : "exist", "fact" : {"name" : "distance", "param" : 2, "closure" : true, "algo" : "average", "pred" : {"name" : "between", "param" : [4, 10]}}},
                                                                                                                                       { "type" : "exist", "fact" : {"name" : "lanegap", "closure" : true, "algo" : "variance", "pred" : {"name" : "greaterthan", "param" : 1.5}}}
                                                                                                                                     ]}
                                                                                             ]},
                                                      { "type" : "exist", "fact" : {"name" : "stop"}}
                                                    ]},
                                     { "type" : "notexist", "fact" : {"name" : "collision"}}
                                   ]

                    } 
                 '''

        self.assert_json(input, expect)


if __name__ == '__main__':
    unittest.main()    