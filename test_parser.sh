#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "========================================="
echo "Testing cub3D Parser"
echo "========================================="
echo ""

# Counter variables
valid_correct=0
valid_incorrect=0
invalid_correct=0
invalid_incorrect=0

# Test invalid maps
echo "${YELLOW}Testing INVALID maps (should fail):${NC}"
echo "========================================="

for map in testing/invalid_maps/*.cub testing/invalid_maps/*; do
    if [ -f "$map" ]; then
        filename=$(basename "$map")
        ./cub3D "$map" > /dev/null 2>&1
        exit_code=$?
        
        if [ $exit_code -ne 0 ]; then
            echo "${GREEN}✓${NC} $filename - Correctly rejected"
            ((invalid_correct++))
        else
            echo "${RED}✗${NC} $filename - SHOULD BE INVALID but was accepted!"
            ((invalid_incorrect++))
        fi
    fi
done

echo ""
echo "${YELLOW}Testing VALID maps (should succeed):${NC}"
echo "========================================="

for map in testing/valid_edgecase/*.cub; do
    if [ -f "$map" ]; then
        filename=$(basename "$map")
        ./cub3D "$map" > /dev/null 2>&1
        exit_code=$?
        
        if [ $exit_code -eq 0 ]; then
            echo "${GREEN}✓${NC} $filename - Correctly accepted"
            ((valid_correct++))
        else
            echo "${RED}✗${NC} $filename - SHOULD BE VALID but was rejected!"
            ((valid_incorrect++))
        fi
    fi
done

echo ""
echo "========================================="
echo "SUMMARY"
echo "========================================="
echo "Invalid maps:"
echo "  ${GREEN}Correctly rejected: $invalid_correct${NC}"
echo "  ${RED}Incorrectly accepted: $invalid_incorrect${NC}"
echo ""
echo "Valid maps:"
echo "  ${GREEN}Correctly accepted: $valid_correct${NC}"
echo "  ${RED}Incorrectly rejected: $valid_incorrect${NC}"
echo ""
total_tests=$((invalid_correct + invalid_incorrect + valid_correct + valid_incorrect))
total_correct=$((invalid_correct + valid_correct))
echo "Total: $total_correct/$total_tests tests passed"

if [ $invalid_incorrect -eq 0 ] && [ $valid_incorrect -eq 0 ]; then
    echo "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo "${RED}Some tests failed!${NC}"
    exit 1
fi
