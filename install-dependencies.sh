#!/bin/sh

set -x
if test -x "$(which apt-get)"; then
  sudo apt-get install libglpk-dev
elif test -x "$(which dnf)"; then
  sudo dnf install glpk-devel
elif test -x "$(which brew)"; then
  brew install glpk
else
  echo "system not supported"
  exit 1
fi