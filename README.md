# OverlapTool

This tool calculates trigger overlaps (and PD overlaps) for a CMS triggering emulator. 

To run it, you'll need a text file with triggers, prescales, and PDs in it. 
see ExampleInputFile.txt

you can run it by 

```` 
./GenerateOverlapInputs.py <ExampleInputFile.txt> 

--mytag <base_output_name> 

--HltTreePath <path_to_HltTree_file> 


optional:    --rate <full_rate>  --nEvents 100  --verbosity <0 or 1>  --debug <0 or 1>

```` 


Please report bugs/comments to jason.kamin@cern.ch 
