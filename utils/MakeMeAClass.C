#include "TFile.h"
#include "TTree.h"

void MakeMeAClass(const char *filename, const char *mytag)
{
  char saythis[500];

  TFile *f1 = TFile::Open(filename);
  TTree *HltTree = (TTree*)f1->GetDirectory("hltbitanalysis")->Get("HltTree");
  sprintf(saythis,"LoopForOverlaps__%s",mytag);
  //cout << saythis << endl;
  HltTree->MakeClass(saythis);

  return;
}
