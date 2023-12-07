#!/bin/bash

# Specify the path to your algorithm executable
ALGORITHM_EXECUTABLE="./build/main/ex1 ../data/records.csv ../data/sorted.csv"

# Specify the range of max heights you want to test
MIN_K_VALUE=1
MAX_K_VALUE=750
INCREMENT=250
FIELD=1

# Counter for segmentation faults
SEG_FAULT_COUNT=0

# Loop through max heights
for ((k = $MIN_K_VALUE; k <= $MAX_K_VALUE; k++)); do
    # Run your algorithm with the current max height and measure the time
    $ALGORITHM_EXECUTABLE $k $FIELD

    # Check the exit status of the last command
    if [ $? -ne 0 ]; then
        echo "Segmentation fault detected for max height: $k"
        ((SEG_FAULT_COUNT++))
    fi

    # Increase the FIELD value every 250 runs
    if [ $((k % INCREMENT)) -eq 0 ]; then
        ((FIELD++))
    fi
done

echo "Script completed"
echo "Number of segmentation faults: $SEG_FAULT_COUNT"
