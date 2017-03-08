import unittest
import json
from SyntaxTranslator import parse_to_json



class TestSyntaxTranslator(unittest.TestCase):
    def setUp(self):
        pass

    def assert_json(self, input_str, expect_str):
        expect = json.loads(expect_str)
        result = json.loads(parse_to_json(input_str))
        self.assertEqual(expect, result)

    def test_empty_input(self):
        self.assertEqual(parse_to_json(''), '')

    def test_no_promise(self):
        self.assertRaises(SyntaxError, parse_to_json('F1: collision.'))

    def test_no_end_symbol(self):
        self.assertRaises(SyntaxError, parse_to_json('promise: collision'))

    def test_simple_promise(self):
        input = '''promise : collision.'''
        expect = '''{"type": "exist", "fact": {"name": "collision"}}'''
        self.assert_json(input, expect)

    # def test_concurrent_promise(self):
    #     input = '''promise : collision && stop.'''
    #     expect = '''{"type" : "sequential",
    #                  "promises" : [{"type": "exist", "fact": {"name": "collision"}},
    #                                {"type": "exist", "fact": {"name": "stop"}}]}'''
    #     self.assert_json(input, expect)


if __name__ == '__main__':
    unittest.main()    