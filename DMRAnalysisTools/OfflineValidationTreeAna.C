#define OfflineValidationTreeAna_cxx
#include "OfflineValidationTreeAna.h"
#include <TH2.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TEntryList.h>
#include <TProfile.h>
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>

void OfflineValidationTreeAna::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L OfflineValidationTreeAna.C
  //      Root > OfflineValidationTreeAna t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
  //
  
  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch

  if (fChain == 0) return;
  
  Double_t cmToUm = 10000;

  Long64_t nentries = fChain->GetEntriesFast();

  // Pixel
  TCanvas *cProfBPixRMSx_DMR_Eta = new TCanvas("cProfXBPix","BPIX-x median vs Eta",700,700);
  TCanvas *cProfFPixRMSx_DMR_Eta = new TCanvas("cProfXFPix","FPIX-x median vs Eta",700,700);
  TCanvas *cProfBPixRMSy_DMR_Eta = new TCanvas("cProfYBPix","BPIX-y median vs Eta",700,700);
  TCanvas *cProfFPixRMSy_DMR_Eta = new TCanvas("cProfYFPix","FPIX-y median vs Eta",700,700);

  TCanvas *cPullBPixRMSx_Eta = new TCanvas("cPullXBPix","BPIX-x pull vs Eta",700,700);
  TCanvas *cPullFPixRMSx_Eta = new TCanvas("cPullXFPix","FPIX-x pull vs Eta",700,700);
  TCanvas *cPullBPixRMSy_Eta = new TCanvas("cPullYBPix","BPIX-y pull vs Eta",700,700);
  TCanvas *cPullFPixRMSy_Eta = new TCanvas("cPullYFPix","FPIX-y pull vs Eta",700,700);

  // Strips
  TCanvas *cProfTIBRMS_DMR_Eta   = new TCanvas("cProfTIB","TIB median vs Eta",700,700);
  TCanvas *cProfTIDRMS_DMR_Eta   = new TCanvas("cProfTID","TID median vs Eta",700,700);
  TCanvas *cProfTOBRMS_DMR_Eta   = new TCanvas("cProfTOB","TOB median vs Eta",700,700);
  TCanvas *cProfTECRMS_DMR_Eta   = new TCanvas("cProfTEC","TEC median vs Eta",700,700);
  
  TCanvas *cPullTIBRMS_Eta   = new TCanvas("cPullTIB","TIB pull vs Eta",700,700);
  TCanvas *cPullTIDRMS_Eta   = new TCanvas("cPullTID","TID pull vs Eta",700,700);
  TCanvas *cPullTOBRMS_Eta   = new TCanvas("cPullTOB","TOB pull vs Eta",700,700);
  TCanvas *cPullTECRMS_Eta   = new TCanvas("cPullTEC","TEC pull vs Eta",700,700);

  // get the maxima/minima
  std::cout<<"overall min(medianX) == "<<fChain->GetMinimum("medianX")*cmToUm<<std::endl;
  std::cout<<"overall max(medianX) == "<<fChain->GetMaximum("medianX")*cmToUm<<std::endl;
  std::cout<<"overall min(medianY) == "<<fChain->GetMinimum("medianY")*cmToUm<<std::endl;
  std::cout<<"overall max(medianY) == "<<fChain->GetMaximum("medianY")*cmToUm<<std::endl;

  TString dets[8] = {"BPix-x","BPix-y","FPix-x","FPix-y","TIB","TID","TOB","TEC"};
  Int_t theSubDetId[8] = {1,1,2,2,3,4,5,6};
  TString theCuts[8];
  Double_t theMaxima[8];
  Double_t theMinima[8];
  std::map<TString,std::pair<Double_t,Double_t > > mymap; 
  std::map<TString,Double_t> nbins; 

  for (UInt_t i=0;i<8;i++){
    theCuts[i]=Form("(subDetId==%i)&&(entries>500)",theSubDetId[i]);
    std::cout<<"*********************************"<<std::endl;
    std::cout<<"i="<<i<<", theCuts["<<i<<"] is:"<<theCuts[i]<<std::endl;
    fChain->Draw(">>eList",theCuts[i], "entrylist"); //Note: "entrylist" is a special option!
    TEntryList * const eList = (TEntryList*)gDirectory->Get("eList");
    if (eList) {
      fChain->SetEntryList(eList);
      std::cout<<"After cut applied ("<<dets[i]<<") :\n";
      if((i==1)||(i==3)){
	std::cout<<"min(y) == "<<fChain->GetMinimum("medianY")*cmToUm<<std::endl;
	std::cout<<"max(y) == "<<fChain->GetMaximum("medianY")*cmToUm<<std::endl;
	theMinima[i]=fChain->GetMinimum("medianY")*cmToUm;
	theMaxima[i]=fChain->GetMaximum("medianY")*cmToUm;

	Double_t theExtreme(0.);
	if (TMath::Abs(theMinima[i])>theMaxima[i]){
	  theExtreme=TMath::Abs(theMinima[i]);
	} else {
	  theExtreme=TMath::Abs(theMaxima[i]);
	}

	std::pair <Double_t,Double_t> foo;
	foo = std::make_pair(-theExtreme*1.10,theExtreme*1.10);
	mymap[dets[i]] = foo;
	nbins[dets[i]] = (foo.second - foo.first)/0.2;

      } else {
	std::cout<<"min(x) == "<<fChain->GetMinimum("medianX")*cmToUm<<std::endl;
	std::cout<<"max(x) == "<<fChain->GetMaximum("medianX")*cmToUm<<std::endl;
	theMinima[i]=fChain->GetMinimum("medianX")*cmToUm;
	theMaxima[i]=fChain->GetMaximum("medianX")*cmToUm;
	
	Double_t theExtreme(0.);
	if (TMath::Abs(theMinima[i])>theMaxima[i]){
	  theExtreme=TMath::Abs(theMinima[i]);
	} else {
	  theExtreme=TMath::Abs(theMaxima[i]);
	}

	std::pair <Double_t,Double_t> foo;
	foo = std::make_pair(-theExtreme*1.10,theExtreme*1.10);
	mymap[dets[i]] = foo;
	nbins[dets[i]] = (foo.second - foo.first)/0.2;
      }
    }

    fChain->SetEntryList(0);
    delete eList;
  }


  for (UInt_t i=0;i<8;i++){
    std::cout<<"mymap["<<dets[i]<<"]: "<<mymap[dets[i]].first<<","<<mymap[dets[i]].second<<std::endl;
  }

  /*
  fChain->Draw(">>eList", "(subDetId==1)&&(entries>30)", "entrylist"); //Note: "entrylist" is a special option!
  TEntryList * const eList = (TEntryList*)gDirectory->Get("eList");
  if (eList) {
    fChain->SetEntryList(eList);
    std::cout<<"After cut applied:\n";
    std::cout<<"min == "<<fChain->GetMinimum("medianX")<<std::endl;
    std::cout<<"max == "<<fChain->GetMaximum("medianX")<<std::endl;
  }
  */

  //%%%%%%%%%% BPix-x %%%%%%%%%%%

  TProfile *profXBpixEta         = new TProfile("profXBPixVsEta",
						"profile x-residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",
						12.,0.,2.8,mymap["BPix-x"].first,mymap["BPix-x"].second,"s");
  
  TH2F     *h2XBpixEta           = new TH2F("h2XBPixVsEta",
					    "profile #mu_{1/2}(res_{x'}) vs #eta (BPix);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",
					    12.,0.,2.8,nbins["BPix-x"],mymap["BPix-x"].first,mymap["BPix-x"].second);
  
  TH1F     *h1XBpixRMSEta        = new TH1F("h1XBpixRMSEta",
					    "RMS of DMR vs #eta;detector pseudorapidity #eta;r.m.s. of DMR [#mum]",
					    12.,0.,2.8);


  TProfile *profNormResXBpixEta  = new TProfile("profXNormResBPixVsEta",
						"Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
						12.,0.,2.8,0.7,1.2,"i");

  TH2F     *h2NormResXBpixEta    = new TH2F("h2XNormResBPixVsEta",
					    "Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
					    12.,0.,2.8,100,0.7,1.2);

  //%%%%%%%%%% FPix-x %%%%%%%%%%%

  TProfile *profXFpixEta         = new TProfile("profXFPixVsEta",
						"profile x-residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",
						12.,0.,2.8,mymap["FPix-x"].first,mymap["FPix-x"].second,"s");
  
  TH2F     *h2XFpixEta           = new TH2F("h2XFPixVsEta",
					    "profile #mu_{1/2}(res_{x'}) vs #eta (FPix);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",
					    12.,0.,2.8,nbins["FPix-x"],mymap["FPix-x"].first,mymap["FPix-x"].second);
  
  TH1F     *h1XFpixRMSEta        = new TH1F("h1XFpixRMSEta",
					    "RMS of DMR vs #eta;detector pseudorapidity #eta;r.m.s. of DMR [#mum]"
					    ,12.,0.,2.8);
  
  TProfile *profNormResXFpixEta  = new TProfile("profXNormResFPixVsEta",
						"Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
						12.,0.,2.8,0.7,1.2,"i");

  TH2F     *h2NormResXFpixEta    = new TH2F("h2XNormResFPixVsEta",
					    "Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
					    12.,0.,2.8,100,0.7,1.2);

  //%%%%%%%%%% BPix-y %%%%%%%%%%%

  TProfile *profYBpixEta         = new TProfile("profYBPixVsEta",
						"profile y-residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{y'})",
						12.,0.,2.8,mymap["BPix-y"].first,mymap["BPix-y"].second,"s");
  
  TH2F     *h2YBpixEta           = new TH2F("h2YBPixVsEta",
					    "profile #mu_{1/2}(res_{y'}) vs #eta (BPix);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{y'})",
					    12.,0.,2.8,nbins["BPix-y"],mymap["BPix-y"].first,mymap["BPix-y"].second);
  
  TH1F     *h1YBpixRMSEta        = new TH1F("h1YBpixRMSEta",
					    "RMS of DMR vs #eta;detector pseudorapidity #eta;r.m.s. of DMR [#mum]",
					    12.,0.,2.8);
  
  TProfile *profNormResYBpixEta  = new TProfile("profYNormResBPixVsEta",
						"Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
						12.,0.,2.8,0.7,1.2,"i");
  
  TH2F     *h2NormResYBpixEta    = new TH2F("h2YNormResBPixVsEta",
					    "Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
					    12.,0.,2.8,100,0.7,1.2);
  
  //%%%%%%%%%% FPix-y %%%%%%%%%%%

  TProfile *profYFpixEta         = new TProfile("profYFPixVsEta",
						"profile y-residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{y'})",
						12.,0.,2.8,mymap["FPix-y"].first,mymap["FPix-y"].second,"s");
  
  TH2F     *h2YFpixEta           = new TH2F("h2YFPixVsEta",
					    "profile #mu_{1/2}(res_{y'}) vs #eta (FPix);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{y'})",
					    12.,0.,2.8,nbins["FPix-y"],mymap["FPix-y"].first,mymap["FPix-y"].second);
  
  TH1F     *h1YFpixRMSEta        = new TH1F("h1YFpixRMSEta",
					    "RMS of DMR vs #eta;detector pseudorapidity #eta;r.m.s. of DMR [#mum]",
					    12.,0.,2.8);
  
  TProfile *profNormResYFpixEta  = new TProfile("profYNormResFPixVsEta",
						"Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
						12.,0.,2.8,0.7,1.2,"i");
  
  TH2F     *h2NormResYFpixEta    = new TH2F("h2YNormResBFixVsEta",
					    "Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
					    12.,0.,2.8,100,0.7,1.2);

  //%%%%%%%%%% TIB %%%%%%%%%%%
  
  TProfile *profTIBEta         = new TProfile("profTIBVsEta",
					      "profile residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",
					      12.,0.,2.8,mymap["TIB"].first,mymap["TIB"].second,"s");
  
  TH2F     *h2TIBEta           = new TH2F("h2TIBVsEta",
					  "profile #mu_{1/2}(res_{x'}) vs #eta (TIB);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",
					  12.,0.,2.8,nbins["TIB"],mymap["TIB"].first,mymap["TIB"].second);
  
  TH1F     *h1TIBRMSEta        = new TH1F("h1TIBRMSEta",
					  "RMS of DMR vs #eta;detector pseudorapidity #eta;r.m.s. of DMR [#mum]",
					  12.,0.,2.8);
  
  TProfile *profNormResTIBEta  = new TProfile("profNormResTIBVsEta",
					      "Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
					      12.,0.,2.8,0.7,1.2,"i");

  TH2F     *h2NormResTIBEta    = new TH2F("h2NormResTIBVsEta",
					    "Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
					    12.,0.,2.8,100,0.7,1.2);

  //%%%%%%%%%% TOB %%%%%%%%%%%

  TProfile *profTOBEta         = new TProfile("profTOBVsEta",
					      "profile residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",
					      12.,0.,2.8,mymap["TOB"].first,mymap["TOB"].second,"s");
  
  TH2F     *h2TOBEta           = new TH2F("h2TOBVsEta",
					  "profile #mu_{1/2}(res_{x'}) vs #eta (TOB);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",
					  12.,0.,2.8,nbins["TOB"],mymap["TOB"].first,mymap["TOB"].second);
  
  TH1F     *h1TOBRMSEta        = new TH1F("h1TOBRMSEta",
					  "RMS of DMR vs #eta;detector pseudorapidity #eta;r.m.s. of DMR [#mum]",
					  12.,0.,2.8);
  
  TProfile *profNormResTOBEta  = new TProfile("profNormResTOBVsEta",
					      "Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
					      12.,0.,2.8,0.7,1.2,"i");

  TH2F     *h2NormResTOBEta    = new TH2F("h2NormResTOBVsEta",
					  "Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
					  12.,0.,2.8,100,0.7,1.2);

  //%%%%%%%%%% TID %%%%%%%%%%%

  TProfile *profTIDEta         = new TProfile("profTIDVsEta",
					      "profile residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",
					      12.,0.,2.8,mymap["TID"].first,mymap["TID"].second,"s");
  
  TH2F     *h2TIDEta           = new TH2F("h2TIDsEta",
					  "profile #mu_{1/2}(res_{x'}) vs #eta (TID);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",
					  12.,0.,2.8,nbins["TID"],mymap["TID"].first,mymap["TID"].second);
  
  TH1F     *h1TIDRMSEta        = new TH1F("h1TIDRMSEta",
					  "RMS of DMR vs #eta;detector pseudorapidity #eta;r.m.s. of DMR [#mum]",
					  12.,0.,2.8);
  
  TProfile *profNormResTIDEta  = new TProfile("profNormResTIDVsEta",
					      "Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
					      12.,0.,2.8,0.7,1.2,"i");

  TH2F     *h2NormResTIDEta    = new TH2F("h2NormResTIDVsEta",
					  "Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
					  12.,0.,2.8,100,0.7,1.2);

  //%%%%%%%%%% TEC %%%%%%%%%%%

  TProfile *profTECEta         = new TProfile("profTECVsEta",
					      "profile residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",
					      12.,0.,2.8,mymap["TEC"].first,mymap["TEC"].second,"s");
  
  TH2F     *h2TECEta           = new TH2F("h2TECVsEta",
					  "profile #mu_{1/2}(res_{x'}) vs #eta (TEC);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",
					  12.,0.,2.8,nbins["TEC"],mymap["TEC"].first,mymap["TEC"].second);
  
  TH1F     *h1TECRMSEta        = new TH1F("h1TECRMSEta",
					  "RMS of DMR vs #eta;detector pseudorapidity #eta;r.m.s. of DMR [#mum]",
					  12.,0.,2.8);
  
  TProfile *profNormResTECEta  = new TProfile("profNormResTECVsEta",
					      "Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
					      12.,0.,2.8,0.7,1.2,"i");

  TH2F     *h2NormResTECEta    = new TH2F("h2NormResTECVsEta",
					  "Normalized residuals RMS vs #eta;detector pseudorapidity #eta;r.m.s. of pull",
					  12.,0.,2.8,100,0.7,1.2);
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if(entries<500.) continue;

      if(subDetId==1){
	
	h2XBpixEta->Fill(TMath::Abs(posEta),medianX*cmToUm);
	profXBpixEta->Fill(TMath::Abs(posEta),medianX*cmToUm);
	profNormResXBpixEta->Fill(TMath::Abs(posEta),rmsNormX);
	h2NormResXBpixEta->Fill(TMath::Abs(posEta),rmsNormX);

	h2YBpixEta->Fill(TMath::Abs(posEta),medianY*cmToUm);
	profYBpixEta->Fill(TMath::Abs(posEta),medianY*cmToUm);
	profNormResYBpixEta->Fill(TMath::Abs(posEta),rmsNormY);
	h2NormResYBpixEta->Fill(TMath::Abs(posEta),rmsNormY);
	
      } else if(subDetId==2){

	profXFpixEta->Fill(TMath::Abs(posEta),medianX*cmToUm);  
	h2XFpixEta->Fill(TMath::Abs(posEta),medianX*cmToUm);  
	profNormResXFpixEta->Fill(TMath::Abs(posEta),rmsNormX);
	h2NormResXFpixEta->Fill(TMath::Abs(posEta),rmsNormX);
	
	//if(medianY*cmToUm>10.) std::cout<<"here comes one: "<<medianY*cmToUm<<"!"<<std::endl;

	profYFpixEta->Fill(TMath::Abs(posEta),medianY*cmToUm);  
	h2YFpixEta->Fill(TMath::Abs(posEta),medianY*cmToUm);  
	profNormResYFpixEta->Fill(TMath::Abs(posEta),rmsNormY);
	h2NormResYFpixEta->Fill(TMath::Abs(posEta),rmsNormY);
	
      }  else if(subDetId==3){             

	profTIBEta->Fill(TMath::Abs(posEta),medianX*cmToUm);  
	h2TIBEta->Fill(TMath::Abs(posEta),medianX*cmToUm);    
	profNormResTIBEta->Fill(TMath::Abs(posEta),rmsNormX);
	h2NormResTIBEta->Fill(TMath::Abs(posEta),rmsNormX);
          
      } else if(subDetId==4){      
  
	profTIDEta->Fill(TMath::Abs(posEta),medianX*cmToUm);  
	h2TIDEta->Fill(TMath::Abs(posEta),medianX*cmToUm); 
	profNormResTIDEta->Fill(TMath::Abs(posEta),rmsNormX);  
	h2NormResTIDEta->Fill(TMath::Abs(posEta),rmsNormX);
   
      }  else if(subDetId==5){

	profTOBEta->Fill(TMath::Abs(posEta),medianX*cmToUm);  
	h2TOBEta->Fill(TMath::Abs(posEta),medianX*cmToUm); 
	profNormResTOBEta->Fill(TMath::Abs(posEta),rmsNormX);
	h2NormResTOBEta->Fill(TMath::Abs(posEta),rmsNormX);
	
      } else if (subDetId==6){
                  
	profTECEta->Fill(TMath::Abs(posEta),medianX*cmToUm);  
	h2TECEta->Fill(TMath::Abs(posEta),medianX*cmToUm);   
	profNormResTECEta->Fill(TMath::Abs(posEta),rmsNormX); 
	h2NormResTECEta->Fill(TMath::Abs(posEta),rmsNormX);
     
      }
  }
  
  setStyle("fire");
 
  // BPIX-x
  makeNiceCanv(cProfBPixRMSx_DMR_Eta);
  cProfBPixRMSx_DMR_Eta->cd();
  gPad->SetRightMargin(0.12);
  makeNice2DPlotStyle(h2XBpixEta);
  h2XBpixEta->Draw("box");
  profXBpixEta->SetLineColor(kRed);
  profXBpixEta->SetFillColor(kRed);
  profXBpixEta->SetFillStyle(3002);
  profXBpixEta->SetMarkerColor(kRed);
  profXBpixEta->SetLineWidth(2.);
  profXBpixEta->SetMarkerStyle(20);
  profXBpixEta->SetMarkerSize(1.4);
  profXBpixEta->Draw("E2same");
  cProfBPixRMSx_DMR_Eta->SaveAs("cProfBPixRMSx_DMR_Eta_"+fChainName+".pdf");
  cProfBPixRMSx_DMR_Eta->SaveAs("cProfBPixRMSx_DMR_Eta_"+fChainName+".root");

  //FPIX-x
  makeNiceCanv(cProfFPixRMSx_DMR_Eta);
  gPad->SetRightMargin(0.12);
  cProfFPixRMSx_DMR_Eta->cd();
  makeNice2DPlotStyle(h2XFpixEta);
  h2XFpixEta->Draw("box");
  profXFpixEta->SetLineColor(kRed);
  profXFpixEta->SetMarkerColor(kRed);
  profXFpixEta->SetFillColor(kRed);
  profXFpixEta->SetFillStyle(3002);
  profXFpixEta->SetLineWidth(2.);
  profXFpixEta->SetMarkerStyle(20);
  profXFpixEta->SetMarkerSize(1.4);
  profXFpixEta->Draw("E2same");
  cProfFPixRMSx_DMR_Eta->SaveAs("cProfFPixRMSx_DMR_Eta_"+fChainName+".pdf");
  cProfFPixRMSx_DMR_Eta->SaveAs("cProfFPixRMSx_DMR_Eta_"+fChainName+".root");

  // BPIX-y
  makeNiceCanv(cProfBPixRMSy_DMR_Eta);
  gPad->SetRightMargin(0.12);
  cProfBPixRMSy_DMR_Eta->cd();
  makeNice2DPlotStyle(h2YBpixEta);
  h2YBpixEta->Draw("box");
  profYBpixEta->SetLineColor(kRed);
  profYBpixEta->SetMarkerColor(kRed);
  profYBpixEta->SetFillColor(kRed);
  profYBpixEta->SetFillStyle(3002);
  profYBpixEta->SetLineWidth(2.);
  profYBpixEta->SetMarkerStyle(20);
  profYBpixEta->SetMarkerSize(1.4);
  profYBpixEta->Draw("E2same");
  cProfBPixRMSy_DMR_Eta->SaveAs("cProfBPixRMSy_DMR_Eta_"+fChainName+".pdf");
  cProfBPixRMSy_DMR_Eta->SaveAs("cProfBPixRMSy_DMR_Eta_"+fChainName+".root");

  //FPIX-y
  makeNiceCanv(cProfFPixRMSy_DMR_Eta);
  gPad->SetRightMargin(0.12);
  cProfFPixRMSy_DMR_Eta->cd();
  makeNice2DPlotStyle(h2YFpixEta);
  h2YFpixEta->Draw("box");
  profYFpixEta->SetLineColor(kRed);
  profYFpixEta->SetMarkerColor(kRed);
  profYFpixEta->SetFillColor(kRed);
  profYFpixEta->SetFillStyle(3002);
  profYFpixEta->SetLineWidth(2.);
  profYFpixEta->SetMarkerStyle(20);
  profYFpixEta->SetMarkerSize(1.4);
  profYFpixEta->Draw("E2same");
  cProfFPixRMSy_DMR_Eta->SaveAs("cProfFPixRMSy_DMR_Eta_"+fChainName+".pdf");
  cProfFPixRMSy_DMR_Eta->SaveAs("cProfFPixRMSy_DMR_Eta_"+fChainName+".root");

  //TIB
  makeNiceCanv(cProfTIBRMS_DMR_Eta);
  gPad->SetRightMargin(0.12);
  cProfTIBRMS_DMR_Eta->cd();
  makeNice2DPlotStyle(h2TIBEta);
  h2TIBEta->Draw("box");
  profTIBEta->SetLineColor(kRed);
  profTIBEta->SetMarkerColor(kRed);
  profTIBEta->SetFillColor(kRed);
  profTIBEta->SetFillStyle(3002);
  profTIBEta->SetLineWidth(2.);
  profTIBEta->SetMarkerStyle(20);
  profTIBEta->SetMarkerSize(1.4);
  profTIBEta->Draw("E2same");
  cProfTIBRMS_DMR_Eta->SaveAs("cProfTIBRMS_DMR_Eta_"+fChainName+".pdf");
  cProfTIBRMS_DMR_Eta->SaveAs("cProfTIBRMS_DMR_Eta_"+fChainName+".root");

  //TOB
  makeNiceCanv(cProfTOBRMS_DMR_Eta);
  gPad->SetRightMargin(0.12);
  cProfTOBRMS_DMR_Eta->cd();
  makeNice2DPlotStyle(h2TOBEta);
  h2TOBEta->Draw("box");
  profTOBEta->SetLineColor(kRed);
  profTOBEta->SetMarkerColor(kRed);
  profTOBEta->SetFillColor(kRed);
  profTOBEta->SetFillStyle(3002);
  profTOBEta->SetLineWidth(2.);
  profTOBEta->SetMarkerStyle(20);
  profTOBEta->SetMarkerSize(1.4);
  profTOBEta->Draw("E2same");
  cProfTOBRMS_DMR_Eta->SaveAs("cProfTOBRMS_DMR_Eta_"+fChainName+".pdf");
  cProfTOBRMS_DMR_Eta->SaveAs("cProfTOBRMS_DMR_Eta_"+fChainName+".root");

  //TID
  makeNiceCanv(cProfTIDRMS_DMR_Eta);
  gPad->SetRightMargin(0.12);
  cProfTIDRMS_DMR_Eta->cd();
  makeNice2DPlotStyle(h2TIDEta);
  h2TIDEta->Draw("box");
  profTIDEta->SetLineColor(kRed);
  profTIDEta->SetMarkerColor(kRed);
  profTIDEta->SetFillColor(kRed);
  profTIDEta->SetFillStyle(3002);
  profTIDEta->SetLineWidth(2.);
  profTIDEta->SetMarkerStyle(20);
  profTIDEta->SetMarkerSize(1.4);
  profTIDEta->Draw("E2same");
  cProfTIDRMS_DMR_Eta->SaveAs("cProfTIDRMS_DMR_Eta_"+fChainName+".pdf");
  cProfTIDRMS_DMR_Eta->SaveAs("cProfTIDRMS_DMR_Eta_"+fChainName+".root");

  //TEC
  makeNiceCanv(cProfTECRMS_DMR_Eta);
  gPad->SetRightMargin(0.12);
  cProfTECRMS_DMR_Eta->cd();
  makeNice2DPlotStyle(h2TECEta);
  h2TECEta->Draw("box");
  profTECEta->SetLineColor(kRed);
  profTECEta->SetMarkerColor(kRed);
  profTECEta->SetFillColor(kRed);
  profTECEta->SetFillStyle(3002);
  profTECEta->SetLineWidth(2.);
  profTECEta->SetMarkerStyle(20);
  profTECEta->SetMarkerSize(1.4);
  profTECEta->Draw("E2same");
  cProfTECRMS_DMR_Eta->SaveAs("cProfTECRMS_DMR_Eta_"+fChainName+".pdf");
  cProfTECRMS_DMR_Eta->SaveAs("cProfTECRMS_DMR_Eta_"+fChainName+".root");

  for (Int_t i=0;i<=profXBpixEta->GetNbinsX();i++){
    h1XBpixRMSEta->SetBinContent(i,profXBpixEta->GetBinError(i));
    h1XFpixRMSEta->SetBinContent(i,profXFpixEta->GetBinError(i));
    h1YBpixRMSEta->SetBinContent(i,profYBpixEta->GetBinError(i));
    h1YFpixRMSEta->SetBinContent(i,profYFpixEta->GetBinError(i));
    h1TIBRMSEta->SetBinContent(i,profTIBEta->GetBinError(i));
    h1TIDRMSEta->SetBinContent(i,profTIDEta->GetBinError(i));
    h1TOBRMSEta->SetBinContent(i,profTOBEta->GetBinError(i));
    h1TECRMSEta->SetBinContent(i,profTECEta->GetBinError(i));

    h1XBpixRMSEta->SetBinError(i,0.0001);
    h1XFpixRMSEta->SetBinError(i,0.0001);
    h1YBpixRMSEta->SetBinError(i,0.0001);
    h1YFpixRMSEta->SetBinError(i,0.0001);
    h1TIBRMSEta->SetBinError(i,0.0001);
    h1TIDRMSEta->SetBinError(i,0.0001);
    h1TOBRMSEta->SetBinError(i,0.0001);
    h1TECRMSEta->SetBinError(i,0.0001);
  }


  makeNicePlotStyleAndColor(h1XBpixRMSEta,0);
  makeNicePlotStyleAndColor(h1XFpixRMSEta,1);
  makeNicePlotStyleAndColor(h1YBpixRMSEta,2);
  makeNicePlotStyleAndColor(h1YFpixRMSEta,3);
  makeNicePlotStyleAndColor(h1TIBRMSEta,4);
  makeNicePlotStyleAndColor(h1TIDRMSEta,5);
  makeNicePlotStyleAndColor(h1TOBRMSEta,6);
  makeNicePlotStyleAndColor(h1TECRMSEta,7);

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  TCanvas *cAllRMSVsEta = new TCanvas("cAllRMSVsEta","RMS of DMR vs #eta (all Tracker)",700,700);
  makeNiceCanv(cAllRMSVsEta);
  cAllRMSVsEta->cd();
  h1XBpixRMSEta->GetYaxis()->SetRangeUser(0.1,7.);
  h1XBpixRMSEta->Draw("HIST");
  h1YBpixRMSEta->Draw("HISTsame");
  h1YFpixRMSEta->Draw("HISTsame");
  h1YFpixRMSEta->Draw("HISTsame");
  h1XFpixRMSEta->Draw("HISTsame");
  h1TIBRMSEta->Draw("HISTsame");
  h1TIDRMSEta->Draw("HISTsame");
  h1TOBRMSEta->Draw("HISTsame");
  h1TECRMSEta->Draw("HISTsame");

  TLegend *leg = new TLegend(0.14,0.7,0.54,0.88);
  leg-> SetNColumns(2);
  leg->SetLineColor(10);
  leg->SetFillColor(10);
  leg->SetTextFont(42);
  leg->AddEntry(h1XBpixRMSEta,"BPix (x)");
  leg->AddEntry(h1XFpixRMSEta,"FPix (x)");
  leg->AddEntry(h1YBpixRMSEta,"BPix (y)");
  leg->AddEntry(h1YFpixRMSEta,"FPix (y)");
  leg->AddEntry(h1TIBRMSEta,"TIB");
  leg->AddEntry(h1TIDRMSEta,"TID");
  leg->AddEntry(h1TOBRMSEta,"TOB");
  leg->AddEntry(h1TECRMSEta,"TEC");
  
  leg->Draw("same");

  cAllRMSVsEta->SaveAs("cALLRMSVsEta_"+fChainName+".root");

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  // BPIX-x
  makeNiceCanv(cPullBPixRMSx_Eta);
  cPullBPixRMSx_Eta->cd();
  gPad->SetRightMargin(0.12);
  makeNice2DPlotStyle(h2NormResXBpixEta);
  h2NormResXBpixEta->Draw("colz");
  profNormResXBpixEta->SetLineColor(kBlue);
  profNormResXBpixEta->SetFillColor(kBlue);
  profNormResXBpixEta->SetFillStyle(3002);
  profNormResXBpixEta->SetMarkerColor(kBlue);
  profNormResXBpixEta->SetLineWidth(2.);
  profNormResXBpixEta->SetMarkerStyle(20);
  profNormResXBpixEta->SetMarkerSize(1.4);
  profNormResXBpixEta->Draw("E1same");
  cPullBPixRMSx_Eta->SaveAs("cPullBPixRMSx_Eta_"+fChainName+".pdf");
  cPullBPixRMSx_Eta->SaveAs("cPullBPixRMSx_Eta_"+fChainName+".root");

  //FPIX-x
  makeNiceCanv(cPullFPixRMSx_Eta);
  gPad->SetRightMargin(0.12);
  cPullFPixRMSx_Eta->cd();
  makeNice2DPlotStyle(h2NormResXFpixEta);
  h2NormResXFpixEta->Draw("colz");
  profNormResXFpixEta->SetLineColor(kBlue);
  profNormResXFpixEta->SetMarkerColor(kBlue);
  profNormResXFpixEta->SetFillColor(kBlue);
  profNormResXFpixEta->SetFillStyle(3002);
  profNormResXFpixEta->SetLineWidth(2.);
  profNormResXFpixEta->SetMarkerStyle(20);
  profNormResXFpixEta->SetMarkerSize(1.4);
  profNormResXFpixEta->Draw("E1same");
  cPullFPixRMSx_Eta->SaveAs("cPullFPixRMSx_Eta_"+fChainName+".pdf");
  cPullFPixRMSx_Eta->SaveAs("cPullFPixRMSx_Eta_"+fChainName+".root");

  // BPIX-y
  makeNiceCanv(cPullBPixRMSy_Eta);
  gPad->SetRightMargin(0.12);
  cPullBPixRMSy_Eta->cd();
  makeNice2DPlotStyle(h2NormResYBpixEta);
  h2NormResYBpixEta->Draw("colz");
  profNormResYBpixEta->SetLineColor(kBlue);
  profNormResYBpixEta->SetMarkerColor(kBlue);
  profNormResYBpixEta->SetFillColor(kBlue);
  profNormResYBpixEta->SetFillStyle(3002);
  profNormResYBpixEta->SetLineWidth(2.);
  profNormResYBpixEta->SetMarkerStyle(20);
  profNormResYBpixEta->SetMarkerSize(1.4);
  profNormResYBpixEta->Draw("E1same");
  cPullBPixRMSy_Eta->SaveAs("cPullBPixRMSy_Eta_"+fChainName+".pdf");
  cPullBPixRMSy_Eta->SaveAs("cPullBPixRMSy_Eta_"+fChainName+".root");

  //FPIX-y
  makeNiceCanv(cPullFPixRMSy_Eta);
  gPad->SetRightMargin(0.12);
  cPullFPixRMSy_Eta->cd();
  makeNice2DPlotStyle(h2NormResYFpixEta);
  h2NormResYFpixEta->Draw("colz");
  profNormResYFpixEta->SetLineColor(kBlue);
  profNormResYFpixEta->SetMarkerColor(kBlue);
  profNormResYFpixEta->SetFillColor(kBlue);
  profNormResYFpixEta->SetFillStyle(3002);
  profNormResYFpixEta->SetLineWidth(2.);
  profNormResYFpixEta->SetMarkerStyle(20);
  profNormResYFpixEta->SetMarkerSize(1.4);
  profNormResYFpixEta->Draw("E1same");
  cPullFPixRMSy_Eta->SaveAs("cPullFPixRMSy_Eta_"+fChainName+".pdf");
  cPullFPixRMSy_Eta->SaveAs("cPullFPixRMSy_Eta_"+fChainName+".root");

  //TIB
  makeNiceCanv(cPullTIBRMS_Eta);
  gPad->SetRightMargin(0.12);
  cPullTIBRMS_Eta->cd();
  makeNice2DPlotStyle(h2NormResTIBEta);
  h2NormResTIBEta->Draw("colz");
  profNormResTIBEta->SetLineColor(kBlue);
  profNormResTIBEta->SetMarkerColor(kBlue);
  profNormResTIBEta->SetFillColor(kBlue);
  profNormResTIBEta->SetFillStyle(3002);
  profNormResTIBEta->SetLineWidth(2.);
  profNormResTIBEta->SetMarkerStyle(20);
  profNormResTIBEta->SetMarkerSize(1.4);
  profNormResTIBEta->Draw("E1same");
  cPullTIBRMS_Eta->SaveAs("cPullTIBRMS_Eta_"+fChainName+".pdf");
  cPullTIBRMS_Eta->SaveAs("cPullTIBRMS_Eta_"+fChainName+".root");

  //TOB
  makeNiceCanv(cPullTOBRMS_Eta);
  gPad->SetRightMargin(0.12);
  cPullTOBRMS_Eta->cd();
  makeNice2DPlotStyle(h2NormResTOBEta);
  h2NormResTOBEta->Draw("colz");
  profNormResTOBEta->SetLineColor(kBlue);
  profNormResTOBEta->SetMarkerColor(kBlue);
  profNormResTOBEta->SetFillColor(kBlue);
  profNormResTOBEta->SetFillStyle(3002);
  profNormResTOBEta->SetLineWidth(2.);
  profNormResTOBEta->SetMarkerStyle(20);
  profNormResTOBEta->SetMarkerSize(1.4);
  profNormResTOBEta->Draw("E1same");
  cPullTOBRMS_Eta->SaveAs("cPullTOBRMS_Eta_"+fChainName+".pdf");
  cPullTOBRMS_Eta->SaveAs("cPullTOBRMS_Eta_"+fChainName+".root");

  //TID
  makeNiceCanv(cPullTIDRMS_Eta);
  gPad->SetRightMargin(0.12);
  cPullTIDRMS_Eta->cd();
  makeNice2DPlotStyle(h2NormResTIDEta);
  h2NormResTIDEta->Draw("colz");
  profNormResTIDEta->SetLineColor(kBlue);
  profNormResTIDEta->SetMarkerColor(kBlue);
  profNormResTIDEta->SetFillColor(kBlue);
  profNormResTIDEta->SetFillStyle(3002);
  profNormResTIDEta->SetLineWidth(2.);
  profNormResTIDEta->SetMarkerStyle(20);
  profNormResTIDEta->SetMarkerSize(1.4);
  profNormResTIDEta->Draw("E1same");
  cPullTIDRMS_Eta->SaveAs("cPullTIDRMS_Eta_"+fChainName+".pdf");
  cPullTIDRMS_Eta->SaveAs("cPullTIDRMS_Eta_"+fChainName+".root");

  //TEC
  makeNiceCanv(cPullTECRMS_Eta);
  gPad->SetRightMargin(0.12);
  cPullTECRMS_Eta->cd();
  makeNice2DPlotStyle(h2NormResTECEta);
  h2NormResTECEta->Draw("colz");
  profNormResTECEta->SetLineColor(kBlue);
  profNormResTECEta->SetMarkerColor(kBlue);
  profNormResTECEta->SetFillColor(kBlue);
  profNormResTECEta->SetFillStyle(3002);
  profNormResTECEta->SetLineWidth(2.);
  profNormResTECEta->SetMarkerStyle(20);
  profNormResTECEta->SetMarkerSize(1.4);
  profNormResTECEta->Draw("E1same");
  cPullTECRMS_Eta->SaveAs("cPullTECRMS_Eta_"+fChainName+".pdf");
  cPullTECRMS_Eta->SaveAs("cPullTECRMS_Eta_"+fChainName+".root");

  makeNiceProfileStyleAndColor(profNormResXBpixEta,0);
  makeNiceProfileStyleAndColor(profNormResYBpixEta,1);
  makeNiceProfileStyleAndColor(profNormResXFpixEta,2);
  makeNiceProfileStyleAndColor(profNormResYFpixEta,3);
  makeNiceProfileStyleAndColor(profNormResTIBEta,4);
  makeNiceProfileStyleAndColor(profNormResTIDEta,5);
  makeNiceProfileStyleAndColor(profNormResTOBEta,6);
  makeNiceProfileStyleAndColor(profNormResTECEta,7);

  TCanvas *cAllRMSNormVsEta = new TCanvas("cAllRMSNormVsEta","RMS of pull vs #eta (all Tracker)",700,700);
  makeNiceCanv(cAllRMSNormVsEta);
  cAllRMSNormVsEta->cd();
  profNormResXBpixEta->GetYaxis()->SetRangeUser(0.,2.);
  profNormResXBpixEta->Draw("e1");
  profNormResYBpixEta->Draw("e1same");
  profNormResXFpixEta->Draw("e1same");
  profNormResYFpixEta->Draw("e1same");
  profNormResTIBEta->Draw("e1same");
  profNormResTIDEta->Draw("e1same");
  profNormResTOBEta->Draw("e1same");
  profNormResTECEta->Draw("e1same");

  TLegend *leg2 = new TLegend(0.14,0.7,0.54,0.88);
  leg2-> SetNColumns(2);
  leg2->SetLineColor(10);
  leg2->SetFillColor(10);
  leg2->SetTextFont(42);
  leg2->AddEntry(profNormResXBpixEta,"BPix (x)");
  leg2->AddEntry(profNormResXFpixEta,"FPix (x)");
  leg2->AddEntry(profNormResYBpixEta,"BPix (y)");
  leg2->AddEntry(profNormResYFpixEta,"FPix (y)");
  leg2->AddEntry(profNormResTIBEta,"TIB");
  leg2->AddEntry(profNormResTIDEta,"TID");
  leg2->AddEntry(profNormResTOBEta,"TOB");
  leg2->AddEntry(profNormResTECEta,"TEC");
  
  leg2->Draw("same");

  cAllRMSNormVsEta->SaveAs("cALLRMSNormVsEta_"+fChainName+".root");

}

