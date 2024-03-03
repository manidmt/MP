#!/bin/bash
/usr/bin//valgrind --leak-check=full ./dist/Debug/GNU-Linux/shopping4 -input ./data/ECommerce162.dataset -index-by UserID -report-by Brand -output ./data/ECommerce162-hit2.dataset < ./tests/validation/ECommerce162.keyboard 1> /dev/null 2>> ./tests/output/ECommerce162.mleaks.full
