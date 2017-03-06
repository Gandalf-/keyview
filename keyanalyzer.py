#!/usr/bin/python

# keyanalyzer.py
#   Author: Austin Voecks

# example usage:
#   python keyanalyzer.py ~/.keyview.log 50 1-5

import sys, operator


def get_substrings(lines, range_start, range_end):
    ''' list of strings, int, int -> dict of strings to lists of ints

    fills a dictionary with the frequencies of substrings, where the substrings
    are sizes from @range_start to @range_end. this is completed in one pass
    '''
    substrings = {}

    for line_index in xrange(len(lines)):
        base = '\t'.join(lines[line_index:line_index + range_start])

        for offset in xrange(range_start, range_end):
            try:
                substrings[base][0] += 1
            except KeyError:
                substrings[base] = [1, offset]

            try:
                base += '\t' + lines[line_index + offset]
            except IndexError:
                pass

    return substrings


def get_total(substrings):
    ''' dict of strings to lists of ints -> float
    '''
    total = 0.0

    for key in substrings:
        if substrings[key][1] == 1:
            total += substrings[key][0]

    return total


def print_substrings(sorted_substrings, num_results, total_keys):
    ''' dict of strings to lists of ints, float -> IO
    '''
    for substring in sorted_substrings[-num_results:][::-1]:

        key_sequence   = substring[0].replace('\t', ' ')
        sequence_count = substring[1][0]

        if total_keys:
            ratio = (substring[1][0] / total_keys) * 100
            print("%-40s%-15d%6.2f" % (key_sequence, sequence_count, ratio))

        else:
            print("%-40s%-15d" % (key_sequence, sequence_count))

    print('\ntotal_keys keys: ' + str(int(total_keys)))


def main():
    ''' string, int, [int | int-int] -> none
    '''
    # agruments
    try:
        file_name      = sys.argv[1]
        num_results    = int(sys.argv[2])
        substring_size = sys.argv[3]

        # given a range or single value?
        try:
            start, end = [int(x) for x in substring_size.split('-')]
        except ValueError:
            start = end = int(substring_size)
        end += 1

    except IndexError:
        print('usage: keyboard_device top_n range')
        sys.exit(1)

    # get file contents
    with open(file_name) as f:
        lines = [x.rstrip(' \n') for x in f.readlines()]

    # get substrings, total keys
    substrings = get_substrings(lines, start, end)
    total_keys = get_total(substrings)

    # sort substrings by frequency
    sorted_substrings = sorted(substrings.items(), key=operator.itemgetter(1))

    # final output
    print_substrings(sorted_substrings, num_results, total_keys)


if __name__ == '__main__':
    main()
