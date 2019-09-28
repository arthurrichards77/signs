#!/bin/bash
grep "Place" < $1 | python process.py
