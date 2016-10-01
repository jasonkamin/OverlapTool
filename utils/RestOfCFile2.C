

    Int_t AlreadyFired_L1_raw = 0;
    Int_t AlreadyFiredHlt_raw = 0;
    Int_t AlreadyFired_L1_psc = 0;
    Int_t AlreadyFiredHlt_psc = 0;

    for(int i=0; i<nPrimaryDSet; i++){
      FiredPD_raw[i] = 0;
      FiredPD_psc[i] = 0;
    }
    for(int i=0; i<nTriggers_L1; i++){
      FiredL1_raw[i] = 0;
      FiredL1_psc[i] = 0;
    }
    for(int i=0; i<nTriggersHlt; i++){
      FiredTr_raw[i] = 0;
      FiredTr_psc[i] = 0;
    }

    for(int i=0; i<nTriggers_L1; i++){
      if(My_L1[i]){
        nEvts_L1_raw[i]++;
        FiredL1_raw[i] = 1;
        if(AlreadyFired_L1_raw==0)
          TotalEvt_L1_raw++;
        AlreadyFired_L1_raw++;

        for(int j=0; j<nTriggersHlt; j++)
          if(MyHLT[j] && L1PathForHLT[j]==i){
            nEvtsHlt_ps1[j]++;
            FiredTr_raw[j] = 1;
            FiredPD_raw[PDForHltID[j]] = 1;
          }

        if(Int_t(nEvts_L1_raw[i])%Int_t(PreScale_L1[i])==0){
          nEvts_L1_psc[i]++;
          FiredL1_psc[i] = 1;
          if(AlreadyFired_L1_psc==0) 
            TotalEvt_L1_psc++;
          AlreadyFired_L1_psc++;

          for(int j=0; j<nTriggersHlt; j++){
            if(MyHLT[j] && L1PathForHLT[j]==i){
              nEvtsHlt_raw[j]++;
              if(AlreadyFiredHlt_raw==0) 
                TotalEvtHlt_raw++;
              AlreadyFiredHlt_raw++;

              if(Int_t(nEvtsHlt_raw[j])%Int_t(PreScaleHlt[j])==0){
                nEvtsHlt_psc[j]++;
                FiredTr_psc[j] = 1;
                FiredPD_psc[PDForHltID[j]] = 1;
                if(AlreadyFiredHlt_psc==0) 
                  TotalEvtHlt_psc++;
                AlreadyFiredHlt_psc++;
              }// HLT pScale

            }// if HLT fired
          }// HLT loop

        }// L1 pScale

      }// if L1 fired
    }// L1 loop



    for(int i=0; i<nTriggers_L1; i++){
      for(int j=0; j<nTriggers_L1; j++){
        if(FiredL1_raw[i]==1 && FiredL1_raw[j]==1)
          h_L1_L1_raw->Fill(i+1,j+1);
        if(FiredL1_psc[i]==1 && FiredL1_psc[j]==1)
          h_L1_L1_psc->Fill(i+1,j+1);
      }
    }

    for(int i=0; i<nTriggersHlt; i++){
      for(int j=0; j<nTriggersHlt; j++){
        if(FiredTr_raw[i]==1 && FiredTr_raw[j]==1)
          h_tr_tr_raw->Fill(i+1,j+1);
        if(FiredTr_psc[i]==1 && FiredTr_psc[j]==1)
          h_tr_tr_psc->Fill(i+1,j+1);
      }
    }

    for(int i=0; i<nTriggersHlt; i++){
      for(int j=0; j<nPrimaryDSet; j++){
        if(FiredTr_raw[i]==1 && FiredPD_raw[j]==1)
          h_tr_pd_raw->Fill(i+1,j+1);
        if(FiredTr_psc[i]==1 && FiredPD_psc[j]==1)
          h_tr_pd_psc->Fill(i+1,j+1);
      }
    }

    for(int i=0; i<nPrimaryDSet; i++){
      for(int j=0; j<nPrimaryDSet; j++){
        if(FiredPD_raw[i]==1 && FiredPD_raw[j]==1)
          h_pd_pd_raw->Fill(i+1,j+1);
        if(FiredPD_psc[i]==1 && FiredPD_psc[j]==1)
          h_pd_pd_psc->Fill(i+1,j+1);
      }
    }

    for(int i=0; i<nTriggers_L1; i++){
      if(FiredL1_psc[i]==1)  h_RatesPerL1_psc->Fill(i+1);
      if(FiredL1_raw[i]==1)  h_RatesPerL1_raw->Fill(i+1);
    }
    for(int i=0; i<nTriggersHlt; i++){
      if(FiredTr_psc[i]==1)  h_RatesPerTr_psc->Fill(i+1);
      if(FiredTr_raw[i]==1)  h_RatesPerTr_raw->Fill(i+1);
    }
    for(int j=0; j<nPrimaryDSet; j++){
      if(FiredPD_psc[j]==1)  h_RatesPerPD_psc->Fill(j+1);
      if(FiredPD_raw[j]==1)  h_RatesPerPD_raw->Fill(j+1);
    }

    Int_t nPDsFired = 0;
    for(int i=0; i<nPrimaryDSet; i++){
      Int_t nOverlappingPDs = 0;
      if(FiredPD_psc[i]==1){
        nPDsFired++;
        for(int j=0; j<nPrimaryDSet; j++)
          if(i!=j && FiredPD_psc[j]==1)
            nOverlappingPDs++;
        h_PDs_NumOtherPDsFired[i]->Fill(nOverlappingPDs);
        if(nOverlappingPDs==0){
          h_UniqueEvts->Fill(i+1);
          h_UniqueEffs->Fill(i+1);
        }
      }//FiredPD_psc==1
    }//loop over PDs
    h_nPDsFired->Fill(nPDsFired);

    evtCount++;
  }//evt loop

  for(int i=0; i<nTriggers_L1; i++){
    SumOfEvt_L1_raw += nEvts_L1_raw[i];
    SumOfEvt_L1_psc += nEvts_L1_psc[i];
  }
  for(int i=0; i<nTriggersHlt; i++){
    SumOfEvtHlt_raw += nEvtsHlt_raw[i];
    SumOfEvtHlt_psc += nEvtsHlt_psc[i];
  }

  h_UniqueEffs->Divide(h_RatesPerPD_psc);
  for(int i=0; i<nPrimaryDSet; i++)  h_TotalEvts ->SetBinContent(i+1,h_RatesPerPD_psc->GetBinContent(i+1));
  h_RatesPerPD_psc->Scale(FullRate/Double_t(evtCount));
  h_RatesPerPD_raw->Scale(FullRate/Double_t(evtCount));
  h_RatesPerL1_psc->Scale(FullRate/Double_t(evtCount));
  h_RatesPerL1_raw->Scale(FullRate/Double_t(evtCount));
  h_RatesPerTr_psc->Scale(FullRate/Double_t(evtCount));
  h_RatesPerTr_raw->Scale(FullRate/Double_t(evtCount));


  cout << endl << endl;

  //################################################################
  // Print the L1 Rates.... 

  cout << "_________________________________________________________________________________________________________________________" << endl;
  cout << "                  TRIGGER STRING                                 |   Raw evts  | PreScale  | Scaled Evts  |     Rate     " << endl;
  cout << " --------------------------------------------------------------- | ----------- | --------  | -----------  | -----------  " << endl;

  for(int i=0; i<nTriggers_L1; i++){
    //if(PreScale_L1[i]>1e8)
      //continue;
    sprintf(saythis, "%63s", TrStrings_L1[i]);
    sprintf(saythis1,"%6d",  nEvts_L1_raw[i]);
    sprintf(saythis2,"%6d",  nEvts_L1_psc[i]);
    sprintf(saythis7,"%6d",  int(nEvts_L1_psc[i]*FullRate/evtCount));
    if(PreScale_L1[i]>199999)  sprintf(saythis3,"  2e5");
    else                       sprintf(saythis3,"%5.0d",Int_t(PreScale_L1[i]));
    cout << saythis << "  |   " << saythis1  << "    |   " << saythis3  << "   |   " << saythis2  << "   |   " << saythis7  << "   " << endl;
  }
  cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
  sprintf(saythis1,"%6d",  SumOfEvt_L1_raw);
  sprintf(saythis2,"%6d",  SumOfEvt_L1_psc);
  sprintf(saythis3,"%6d",  TotalEvt_L1_raw);
  sprintf(saythis4,"%6d",  TotalEvt_L1_psc);
  sprintf(saythis5,"%4.3f",  double(TotalEvt_L1_raw)/double(SumOfEvt_L1_raw));
  sprintf(saythis6,"%4.3f",  double(TotalEvt_L1_psc)/double(SumOfEvt_L1_psc));
  sprintf(saythis7,"%6d",  int(TotalEvt_L1_psc*FullRate/evtCount));
  cout << "                  SIMPLE SUM                                     |   " << saythis1  << "  |           |   " << saythis2  << "   " << endl;
  cout << "             ACTUAL AFTER OVERLAPS                               |   " << saythis3  << "    |           |   " << saythis4  << "    | " << saythis7 << "   " << endl;
  cout << "             Ratio of simple_sum/total                           |~   " << saythis5  << "   ~|           |~  " << saythis6  << "  ~" << endl;
  cout << "_________________________________________________________________________________________________________________________" << endl;
  cout << endl;
  //
  //################################################################




  //################################################################
  // Print the HLT Rates.... 

  cout << endl;
  cout << "__________________________________________________________________________________________________________________________________________________   " << endl;
  cout << "                  TRIGGER STRING                                 |  NoPS Evts  | L1 pScale | Fed HLT Evts| HLT pScale|  Rec Events |     Rate    |   " << endl;
  cout << " --------------------------------------------------------------- | ----------- | --------- | ----------- | --------- | ----------- | ----------- |   " << endl;

  for(int i=0; i<nTriggersHlt; i++){
    if(PreScaleHlt[i]>1e8)
      continue;
    sprintf(saythis, "%60s", TrStringsHlt[i]);
    sprintf(saythis1,"%6d",  nEvtsHlt_ps1[i]);
    sprintf(saythis2,"%6d",  nEvtsHlt_raw[i]);
    sprintf(saythis3,"%6d",  nEvtsHlt_psc[i]);
    sprintf(saythis7,"%6d",  int(nEvtsHlt_psc[i]*FullRate/evtCount));
    if(PreScaleHlt[i]>199999)  sprintf(saythis5,"  2e5");
    else                       sprintf(saythis5,"%5d",Int_t(PreScaleHlt[i]));
    if(PreScale_L1[L1PathForHLT[i]]>199999)  sprintf(saythis6,"  2e5");
    else                                     sprintf(saythis6,"%5d",Int_t(PreScale_L1[L1PathForHLT[i]]));
    cout << saythis << "  |   " << saythis1  << "    |   " << saythis6  << "   |   " << saythis2  << "    |   " << saythis5  << "   |   " << saythis3 << "    |   " << saythis7 << "    |   " << endl;
  }
  cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
  sprintf(saythis1,"%6d",  SumOfEvtHlt_raw);
  sprintf(saythis2,"%4d",  SumOfEvtHlt_psc);
  sprintf(saythis3,"%6d",  TotalEvtHlt_raw);
  sprintf(saythis4,"%4d",  TotalEvtHlt_psc);
  sprintf(saythis5,"%4.3f",  double(TotalEvtHlt_raw)/double(SumOfEvtHlt_raw));
  sprintf(saythis6,"%4.3f",  double(TotalEvtHlt_psc)/double(SumOfEvtHlt_psc));
  sprintf(saythis7,"%6d",  int(TotalEvtHlt_psc*FullRate/evtCount));
  cout << "                     SIMPLE SUM                                                            |   " << saythis1  << "   |           |   " << saythis2  << "   " << endl;
  cout << "                ACTUAL AFTER OVERLAPS                                                      |   " << saythis3  << "    |           |   " << saythis4  << "    | " << saythis7 << endl;
  cout << "                Ratio of simple_sum/total                                                  |~   " << saythis5  << "   ~|           |~  " << saythis6  << "  ~" << endl;
  cout << "_____________________________________________________________________________________________________________________________________________  " << endl;
  cout << endl;
  //################################################################
  // Print the L1 Rates.... 


  for(int i=0; i<nTriggersHlt; i++){
    h_tr_tr_raw     ->GetXaxis()->SetBinLabel(i+1,TrStringsHlt[i]);
    h_tr_tr_psc     ->GetXaxis()->SetBinLabel(i+1,TrStringsHlt[i]);
    h_tr_tr_raw     ->GetYaxis()->SetBinLabel(i+1,TrStringsHlt[i]);
    h_tr_tr_psc     ->GetYaxis()->SetBinLabel(i+1,TrStringsHlt[i]);
    h_tr_pd_raw   ->GetXaxis()->SetBinLabel(i+1,TrStringsHlt[i]);
    h_tr_pd_psc   ->GetXaxis()->SetBinLabel(i+1,TrStringsHlt[i]);
    h_RatesPerTr_psc->GetXaxis()->SetBinLabel(i+1,TrStringsHlt[i]);
    h_RatesPerTr_raw->GetXaxis()->SetBinLabel(i+1,TrStringsHlt[i]);
    h_PS_for_trigHlt->GetXaxis()->SetBinLabel(i+1,TrStringsHlt[i]);
  }
  for(int i=0; i<nTriggers_L1; i++){
    h_L1_L1_raw     ->GetXaxis()->SetBinLabel(i+1,TrStrings_L1[i]);
    h_L1_L1_psc     ->GetXaxis()->SetBinLabel(i+1,TrStrings_L1[i]);
    h_L1_L1_raw     ->GetYaxis()->SetBinLabel(i+1,TrStrings_L1[i]);
    h_L1_L1_psc     ->GetYaxis()->SetBinLabel(i+1,TrStrings_L1[i]);
    h_RatesPerL1_psc->GetXaxis()->SetBinLabel(i+1,TrStrings_L1[i]);
    h_RatesPerL1_raw->GetXaxis()->SetBinLabel(i+1,TrStrings_L1[i]);
    h_PS_for_trig_L1->GetXaxis()->SetBinLabel(i+1,TrStrings_L1[i]);
  }

  cout << endl << "At " << Int_t(FullRate/1000.0) << " kHz : " << endl;
  for(int i=0; i<nPrimaryDSet; i++){
    h_tr_pd_raw   ->GetYaxis()->SetBinLabel(i+1,PDStrings[i]);
    h_tr_pd_psc   ->GetYaxis()->SetBinLabel(i+1,PDStrings[i]);
    h_pd_pd_raw     ->GetXaxis()->SetBinLabel(i+1,PDStrings[i]);
    h_pd_pd_psc     ->GetXaxis()->SetBinLabel(i+1,PDStrings[i]);
    h_pd_pd_raw     ->GetYaxis()->SetBinLabel(i+1,PDStrings[i]);
    h_pd_pd_psc     ->GetYaxis()->SetBinLabel(i+1,PDStrings[i]);
    h_UniqueEvts    ->GetXaxis()->SetBinLabel(i+1,PDStrings[i]);
    h_UniqueEffs    ->GetXaxis()->SetBinLabel(i+1,PDStrings[i]);
    h_RatesPerPD_psc->GetXaxis()->SetBinLabel(i+1,PDStrings[i]);
    h_RatesPerPD_raw->GetXaxis()->SetBinLabel(i+1,PDStrings[i]);

    cout << PDStrings[i] << " has a rate of " << Int_t(h_RatesPerPD_psc->GetBinContent(i+1)) << "  Hz\tand has " << 
      h_UniqueEvts ->GetBinContent(i+1) << "\tunique events out of " << 
      h_TotalEvts  ->GetBinContent(i+1) << " \tfor and UniqueEff: " << 
      h_UniqueEffs ->GetBinContent(i+1) << " . " << endl;
  }

  Int_t TotalEventsStored = Int_t(h_RatesPerPD_psc->Integral(1,nPrimaryDSet)*Double_t(evtCount)/FullRate);
  Int_t RedundantEvents   = TotalEventsStored - h_nPDsFired->Integral(2,-1);

  cout << endl << endl;
  cout << " We stored a total of  " << TotalEventsStored << "  events." << endl;
  cout << " Events that were in some way redundant:  " << RedundantEvents << endl;
  cout << " If we had only 1 PD, we'd have stored  " << h_nPDsFired->Integral(2,-1) << "  events." << endl;

  cout << endl;
  cout << "_______________________________________________________________________" << endl;
  cout << "We examined " << evtCount << " / " << nentries << " events." << endl << endl;;


  TLine *line_PDEdges[nPrimaryDSet];
  TBox *DiagonalBox[nPrimaryDSet];
  for(int i=0; i<nPrimaryDSet; i++){
    line_PDEdges[i] = new TLine(0.5,i+0.5,nTriggersHlt+0.5,i+0.5);
    line_PDEdges[i]->SetLineWidth(2);
    if(i==0)
      DiagonalBox[i] = new TBox(0.5,i+0.5,PDIndexEdges[i]+0.5,i+1.5);
    else if(i<nPrimaryDSet-1)
      DiagonalBox[i] = new TBox(PDIndexEdges[i-1]+0.5,i+0.5,PDIndexEdges[i]+0.5,i+1.5);
    else
      DiagonalBox[i] = new TBox(PDIndexEdges[i-1]+0.5,i+0.5,nTriggersHlt+0.5,i+1.5);
    //sprintf(saythis,"DiagonalBox_%d",i);
    //DiagonalBox[i]->SetName(saythis);
    DiagonalBox[i]->SetFillStyle(0);
    DiagonalBox[i]->SetLineWidth(4);
    DiagonalBox[i]->SetLineColor(kRed);
  }
  TLine *line_TrEdges[nPrimaryDSet];
  for(int i=0; i<nPrimaryDSet; i++){
    line_TrEdges[i] = new TLine(PDIndexEdges[i]+0.5,0.5, PDIndexEdges[i]+0.5,nPrimaryDSet+0.5);
    line_TrEdges[i]->SetLineWidth(2);
  }
  gStyle->SetOptStat(0);
  //gStyle->SetPalette(kRainBow,0);
  gStyle->SetPalette(55,0);
  TCanvas *c1_raw = new TCanvas("c1_raw","c1_raw",1000,600);
  c1_raw->SetLeftMargin(0.18);
  c1_raw->SetLogz();
  h_tr_pd_raw->Draw("colz");
  for(int i=0; i<nPrimaryDSet; i++){
    line_TrEdges[i]->Draw("same");
    line_PDEdges[i]->Draw("same");
    DiagonalBox[i] ->Draw("same");
  }

  TCanvas *c1_psc = new TCanvas("c1_psc","c1_psc",1000,600);
  c1_psc->SetLeftMargin(0.18);
  c1_psc->SetLogz();
  h_tr_pd_psc->Draw("colz");
  for(int i=0; i<nPrimaryDSet; i++){
    line_TrEdges[i]->Draw("same");
    line_PDEdges[i]->Draw("same");
    DiagonalBox[i] ->Draw("same");
  }

  TCanvas *c1_rates = new TCanvas("c1_rates","c1_rates",800,800);
  c1_rates->Divide(2,2);
  c1_rates->cd(1);
  h_RatesPerPD_psc->Draw();
  c1_rates->cd(2);
  h_RatesPerPD_raw->Draw();
  c1_rates->cd(3);
  h_RatesPerTr_psc->Draw();
  c1_rates->cd(4);
  h_RatesPerTr_raw->Draw();


  TFile *fout = new TFile(outputfile,"RECREATE");
  h_L1_L1_raw->Write();
  h_L1_L1_psc->Write();
  h_tr_tr_raw->Write();
  h_tr_tr_psc->Write();
  h_tr_pd_raw->Write();
  h_tr_pd_psc->Write();
  h_pd_pd_raw->Write();
  h_pd_pd_psc->Write();
  h_TotalEvts->Write();
  h_UniqueEvts->Write();
  h_UniqueEffs->Write();
  h_nPDsFired->Write();
  for(int i=0; i<nPrimaryDSet; i++)
    h_PDs_NumOtherPDsFired[i]->Write();
  h_RatesPerPD_psc->Write();
  h_RatesPerPD_raw->Write();
  h_RatesPerL1_psc->Write();
  h_RatesPerL1_raw->Write();
  h_RatesPerTr_psc->Write();
  h_RatesPerTr_raw->Write();
  h_PS_for_trig_L1->Write();
  h_PS_for_trigHlt->Write();
  c1_raw->Write();
  c1_psc->Write();
  c1_rates->Write();
  fout->Close();


  cout << "Assumed Full Rate:  " << FullRate << " Hz" << endl;
  cout << "Accept Rate:  " << float(TotalEvtHlt_psc)/float(evtCount) << endl;
  cout << "Output Rate:  " << FullRate*float(TotalEvtHlt_psc)/float(evtCount) << endl;



}

