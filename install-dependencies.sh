#!/bin/sh

set -x
if test -x "$(which apt-get)"; then
  sudo apt-get install coinor-libosi-dev coinor-libosi-doc coinor-libosi1v5 libglpk-dev
elif test -x "$(which dnf)"; then
  sudo dnf install coin-or-Osi coin-or-Osi-devel
elif test -x "$(which brew)"; then
  brew install osi
else
  echo "system not supported"
  exit 1
fi