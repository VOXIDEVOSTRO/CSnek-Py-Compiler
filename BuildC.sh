#!/usr/bin/env bash
set -e

# Colors
GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"

# default (Debian/Ubuntu)
PREFIX="/usr/local"

for arg in "$@"; do
  case $arg in
    --prefix=*)
      PREFIX="${arg#*=}"
      shift
      ;;
    *)
      echo -e "${RED}no option: $arg${RESET}"
      echo "usage: $0 [--prefix=/path/to/prefix]"
      exit 1
      ;;
  esac
done

echo -e "${GREEN}> cleaning...${RESET}"
make Clean || { echo -e "${RED}> Clean failed${RESET}"; exit 1; }

echo -e "${GREEN}> building snek...${RESET}"
make || { echo -e "${RED}> Build failed${RESET}"; exit 1; }

echo -e "${GREEN}> installing to $PREFIX/bin...${RESET}"
make installLinux PREFIX="$PREFIX" || { echo -e "${RED}> Install failed${RESET}"; exit 1; }

echo -e "${GREEN}> Installation completed successfully${RESET}"