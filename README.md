# OverlapTool

This tool calculates trigger overlaps (and PD overlaps) for a CMS triggering emulator. 

To run it, you'll need a text file with triggers, prescales, and PDs in it. 
see ExampleInputFile.txt

you can run it by 

```` 
./GenerateOverlapInputs.py <ExampleInputFile.txt> 

--mytag <base_output_name> 

--HltTreePath <path_to_HltTree_file> 


optional:    --rate <full_rate>  --nEvents 100  --verbosity <0 or 1>  --debug <0 or 1>  --customrootpath <path_to_root>

```` 

'--mytag' is simply to give the output a unique name.  ie. the output would be called Overlaps_base_output_name.root

'--rate' is your desired raw input collision rate by which the HltTree results get scaled. 

'--HltTreePath' is the path to your root file containing the HltTree. The tree should be in a TDirectory called 'hltbitanalysis'

'--nEvents' is the number of HltTree events you want to run over. 

'--customrootpath' point to your preferred root installation

'--debug', if this is *not* set to 0 then the .C(.h) MakeClass files will be generated but *not* run (you can do it by hand).

Please report bugs/comments to jason.kamin@cern.ch 
