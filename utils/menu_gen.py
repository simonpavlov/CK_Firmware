#!/usr/bin/env python2
import re, sys

dot = re.compile('^(\*+) ')

if __name__ == '__main__':
    f = open(sys.argv[1], 'r')

    l = f.readline()
    state = len(dot.match(l).group(0)) - 1
    print 'add_item(list, %s);' % l[state+1:-1]

    for l in f:
        newstate = len(dot.match(l).group(0)) - 1
        if (newstate > state):
            print 'add_list(list, list->edge);'
            print 'list = list->edge->child;'
        elif (newstate < state):
            for i in range(0, state - newstate):
                print 'add_item(list, "back", NULL);'
                print 'list->edge->child = list->parent;'
                print 'list = list->parent;'
        print 'add_item(list, %s);' % l[newstate+1:-1]
        state = newstate

    if state > 1:
        for i in range(0, state - 1):
            print 'add_item(list, "back", NULL);'
            print 'list->edge->child = list->parent;'
            print 'list = list->parent;'

