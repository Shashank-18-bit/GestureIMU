#!/bin/bash

txt_files=$(ls txt/)
csv_files=$(ls csv/)

echo "Removed the txt files" 
echo $txt_files 
echo "Removed the csv files"
echo $csv_files

rm csv/* txt/*
