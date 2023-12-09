# Merge Sort Implementation

This repository contains an implementation of the Merge Sort algorithm in two versions: one utilizing threads for parallel processing and another without using threads.

## Description

Merge Sort is a divide-and-conquer algorithm that recursively divides the input array into smaller sub-arrays until each sub-array consists of a single element. It then merges these sub-arrays in a sorted order to produce a fully sorted array.

### With Threads

The `merge_sort_Using_Threads` directory contains an implementation of Merge Sort that leverages multithreading to enhance performance. This version splits the array into sub-arrays and utilizes threads to concurrently sort these sub-arrays before merging them back together.

#### Usage

To compile the program:

```bash
cd /folder path/merge_sort_Using_Threads
make
