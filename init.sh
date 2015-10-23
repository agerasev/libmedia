#!/bin/sh

git submodule init
git submodule update

cd libmedia
git submodule init
git submodule update