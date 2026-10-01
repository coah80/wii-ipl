import contextlib
import io
import unittest
from unittest.mock import Mock, mock_open, patch

import pool_diff


class PoolDiffTests(unittest.TestCase):
    def read_pool(self, data):
        elf = Mock()
        section = None if data is None else Mock()
        if section is not None:
            section.data.return_value = data
        elf.get_section_by_name.return_value = section
        with patch('builtins.open', mock_open(read_data=b'')), patch.object(pool_diff, 'ELFFile', return_value=elf):
            result = pool_diff.pool('test.o')
        elf.get_section_by_name.assert_called_once_with('.data')
        return result

    def compare(self, left, right):
        with patch.object(pool_diff.sys, 'argv', ['pool_diff.py', 'left.o', 'right.o']), \
             patch.object(pool_diff, 'pool', side_effect=[left, right]), \
             contextlib.redirect_stdout(io.StringIO()):
            return pool_diff.main()

    def test_missing_data_has_no_strings(self):
        self.assertEqual(self.read_pool(None), [])

    def test_empty_data_has_no_strings(self):
        self.assertEqual(self.read_pool(b''), [])

    def test_existing_string_extraction(self):
        self.assertEqual(self.read_pool(b'abc\x00hello\x00world\x00'), [(4, 'hello'), (10, 'world')])

    def test_two_missing_pools_match(self):
        self.assertEqual(self.compare([], []), 0)

    def test_identical_pools_match(self):
        self.assertEqual(self.compare([(0, 'hello')], [(0, 'hello')]), 0)

    def test_changed_string_fails(self):
        self.assertEqual(self.compare([(0, 'hello')], [(0, 'world')]), 1)

    def test_missing_left_pool_does_not_hide_strings(self):
        self.assertEqual(self.compare([], [(0, 'hello')]), 1)

    def test_missing_right_pool_does_not_hide_strings(self):
        self.assertEqual(self.compare([(0, 'hello')], []), 1)


if __name__ == '__main__':
    unittest.main()
