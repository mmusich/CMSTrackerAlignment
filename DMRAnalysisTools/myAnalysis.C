#define myAnalysis_cxx
#include "myAnalysis.h"
#include <TH2.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TProfile.h>
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>

void myAnalysis::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L myAnalysis.C
  //      Root > myAnalysis t
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
  
  Long64_t nentries = fChain->GetEntriesFast();
  TCanvas *c  = new TCanvas("c","BPIX-y median",700,700);
  TCanvas *cX = new TCanvas("cX","BPIX-y median",700,700);
  TCanvas *cR = new TCanvas("cR","BPIX-y median",700,700);
  TCanvas *cZ = new TCanvas("cZ","BPIX-y median",700,700);
  TCanvas *cL = new TCanvas("cL","BPIX-y median",700,700);

  TCanvas *cProfBPixRMSx_DMR_Eta = new TCanvas("cProfXBPix","BPIX-x median vs Eta",700,700);
  TCanvas *cProfFPixRMSx_DMR_Eta = new TCanvas("cProfXFPix","FPIX-x median vs Eta",700,700);

  TCanvas *cProfBPixRMSy_DMR_Eta = new TCanvas("cProfYBPix","BPIX-y median vs Eta",700,700);
  TCanvas *cProfFPixRMSy_DMR_Eta = new TCanvas("cProfYFPix","FPIX-y median vs Eta",700,700);

  TCanvas *cProfTIBRMS_DMR_Eta   = new TCanvas("cProfTIB","TIB median vs Eta",700,700);
  TCanvas *cProfTIDRMS_DMR_Eta   = new TCanvas("cProfTID","TID median vs Eta",700,700);
  TCanvas *cProfTOBRMS_DMR_Eta   = new TCanvas("cProfTOB","TOB median vs Eta",700,700);
  TCanvas *cProfTECRMS_DMR_Eta   = new TCanvas("cProfTEC","TEC median vs Eta",700,700);
    
  TH1F *hBPIXAll  = new TH1F("h1BPIXAll","BPIX-y DMR;#mu_{1/2}(v_{pred}-v_{rec}) (cm); modules",30,-0.001,0.001);
  TH1F *hBPIXL1   = new TH1F("h1BPIXL1","Layer 1;#mu_{1/2}(v_{pred}-v_{rec}) (cm); modules",30,-0.001,0.001);
  TH1F *hBPIXL2   = new TH1F("h1BPIXL2","Layer 2;#mu_{1/2}(v_{pred}-v_{rec}) (cm); modules",30,-0.001,0.001);
  TH1F *hBPIXL3   = new TH1F("h1BPIXL3","Layer 3;#mu_{1/2}(v_{pred}-v_{rec}) (cm); modules",30,-0.001,0.001);

  TH1F *hBPIXPosX = new TH1F("h1BPIXPosX","x>0;#mu_{1/2}(v_{pred}-v_{rec}) (cm); modules",30,-0.001,0.001);
  TH1F *hBPIXNegX = new TH1F("h1BPIXNegX","x<0;#mu_{1/2}(v_{pred}-v_{rec}) (cm); modules",30,-0.001,0.001);
  
  TH1F *hBPIXPosR = new TH1F("h1BPIXPosR","outward ponting;#mu_{1/2}(v_{pred}-v_{rec}) (cm); modules",30,-0.001,0.001);
  TH1F *hBPIXNegR = new TH1F("h1BPIXNegR","inward pointing;#mu_{1/2}(v_{pred}-v_{rec}) (cm); modules",30,-0.001,0.001);
  
  TH1F *hBPIXPosZ = new TH1F("h1BPIXPosZ","z>0;#mu_{1/2}(v_{pred}-v_{rec}) (cm); modules",30,-0.001,0.001);
  TH1F *hBPIXNegZ = new TH1F("h1BPIXNegZ","z<0;#mu_{1/2}(v_{pred}-v_{rec}) (cm); modules",30,-0.001,0.001);

  TProfile *profXBpixEta  = new TProfile("profXBPixVsEta","profile x-residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",10.,0.,2.5,-10.,10.,"s");
  TH2F     *h2XBpixEta    = new TH2F("h2XBPixVsEta","profile #mu_{1/2}(res_{x'}) vs #eta (BPix);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",10.,0.,2.5,100,-10.,10.);
  TH1F     *h1XBpixRMSEta = new TH1F("h1XBpixRMSEta","RMS of DMR vs #eta (BPix-x);detector pseudorapidity #eta;r.m.s. of DMR [#mum]",10.,0.,2.5);
  TProfile *profNormResXBpixEta  = new TProfile("profXNormResBPixVsEta","Normalized residuals RMS vs #eta (BPIx-x);detector pseudorapidity #eta;r.m.s. of pull",10.,0.,2.5,0.,1.5,"i");

  TProfile *profXFpixEta  = new TProfile("profXFPixVsEta","profile x-residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",10.,0.,2.5,-10.,10.,"s");
  TH2F     *h2XFpixEta    = new TH2F("h2XFPixVsEta","profile #mu_{1/2}(res_{x'}) vs #eta (FPix);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",10.,0.,2.5,100,-10.,10.);
  TH1F     *h1XFpixRMSEta = new TH1F("h1XFpixRMSEta","RMS of DMR vs #eta (FPix-x);detector pseudorapidity #eta;r.m.s. of DMR [#mum]",10.,0.,2.5);
  TProfile *profNormResXFpixEta  = new TProfile("profXNormResFPixVsEta","Normalized residuals RMS vs #eta (FPIx-x);detector pseudorapidity #eta;r.m.s. of pull",10.,0.,2.5,0.,1.5,"i");

  TProfile *profYBpixEta  = new TProfile("profYBPixVsEta","profile y-residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{y'})",10.,0.,2.5,-10.,10.,"s");
  TH2F     *h2YBpixEta    = new TH2F("h2XBPixVsEta","profile #mu_{1/2}(res_{y'}) vs #eta (BPix);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{y'})",10.,0.,2.5,100,-10.,10.);
  TH1F     *h1YBpixRMSEta = new TH1F("h1YBpixRMSEta","RMS of DMR vs #eta (BPix-y);detector pseudorapidity #eta;r.m.s. of DMR [#mum]",10.,0.,2.5);
  TProfile *profNormResYBpixEta  = new TProfile("profYNormResBPixVsEta","Normalized residuals RMS vs #eta (BPIx-y);detector pseudorapidity #eta;r.m.s. of pull",10.,0.,2.5,0.,1.5,"i");

  TProfile *profYFpixEta  = new TProfile("profYFPixVsEta","profile y-residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{y'})",10.,0.,2.5,-10.,10.,"s");
  TH2F     *h2YFpixEta    = new TH2F("h2YFPixVsEta","profile #mu_{1/2}(res_{y'}) vs #eta (FPix);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{y'})",10.,0.,2.5,100,-10.,10.);
  TH1F     *h1YFpixRMSEta = new TH1F("h1YFpixRMSEta","RMS of DMR vs #eta (FPix-y);detector pseudorapidity #eta;r.m.s. of DMR [#mum]",10.,0.,2.5);
  TProfile *profNormResYFpixEta  = new TProfile("profYNormResFPixVsEta","Normalized residuals RMS vs #eta (FPIx-y);detector pseudorapidity #eta;r.m.s. of pull",10.,0.,2.5,0.,1.5,"i");

  TProfile *profTIBEta    = new TProfile("profTIBVsEta","profile residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",10.,0.,2.5,-10.,10.,"s");
  TH2F     *h2TIBEta      = new TH2F("h2TIBVsEta","profile #mu_{1/2}(res_{x'}) vs #eta (TIB);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",10.,0.,2.5,100,-10.,10.);
  TH1F     *h1TIBRMSEta   = new TH1F("h1TIBRMSEta","RMS of DMR vs #eta (TIB);detector pseudorapidity #eta;r.m.s. of DMR [#mum]",10.,0.,2.5);
  TProfile *profNormResTIBEta  = new TProfile("profNormResTIBVsEta","Normalized residuals RMS vs #eta (TIB);detector pseudorapidity #eta;r.m.s. of pull",10.,0.,2.5,0.,1.5,"i");

  TProfile *profTOBEta    = new TProfile("profTOBVsEta","profile residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",10.,0.,2.5,-10.,10.,"s");
  TH2F     *h2TOBEta      = new TH2F("h2TOBVsEta","profile #mu_{1/2}(res_{x'}) vs #eta (TOB);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",10.,0.,2.5,100,-10.,10.);
  TH1F     *h1TOBRMSEta   = new TH1F("h1TOBRMSEta","RMS of DMR vs #eta (TOB);detector pseudorapidity #eta;r.m.s. of DMR [#mum]",10.,0.,2.5);
  TProfile *profNormResTOBEta  = new TProfile("profNormResTOBVsEta","Normalized residuals RMS vs #eta (TOB);detector pseudorapidity #eta;r.m.s. of pull",10.,0.,2.5,0.,1.5,"i");

  TProfile *profTIDEta    = new TProfile("profTIDVsEta","profile residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",10.,0.,2.5,-10.,10.,"s");
  TH2F     *h2TIDEta      = new TH2F("h2TIDsEta","profile #mu_{1/2}(res_{x'}) vs #eta (TID);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",10.,0.,2.5,100,-10.,10.);
  TH1F     *h1TIDRMSEta   = new TH1F("h1TIDRMSEta","RMS of DMR vs #eta (TID);detector pseudorapidity #eta;r.m.s. of DMR [#mum]",10.,0.,2.5);
  TProfile *profNormResTIDEta  = new TProfile("profNormResTIDVsEta","Normalized residuals RMS vs #eta (TID);detector pseudorapidity #eta;r.m.s. of pull",10.,0.,2.5,0.,1.5,"i");

  TProfile *profTECEta    = new TProfile("profTECVsEta","profile residual vs #eta;detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",10.,0.,2.5,-10.,10.,"s");
  TH2F     *h2TECEta      = new TH2F("h2TECVsEta","profile #mu_{1/2}(res_{x'}) vs #eta (TEC);detector pseudorapidity #eta;median of residual #mu_{1/2}(res_{x'})",10.,0.,2.5,100,-10.,10.);
  TH1F     *h1TECRMSEta   = new TH1F("h1TECRMSEta","RMS of DMR vs #eta (TEC);detector pseudorapidity #eta;r.m.s. of DMR [#mum]",10.,0.,2.5);
  TProfile *profNormResTECEta  = new TProfile("profNormResTECVsEta","Normalized residuals RMS vs #eta (TEC);detector pseudorapidity #eta;r.m.s. of pull",10.,0.,2.5,0.,1.5,"i");

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if(isDoubleSide==1&&entries<30.) continue;

      if(subDetId==1){

	hBPIXAll->Fill(medianX);
	
	h2XBpixEta->Fill(TMath::Abs(posEta),medianX*10000.);
	profXBpixEta->Fill(TMath::Abs(posEta),medianX*10000.);
	profNormResXBpixEta->Fill(TMath::Abs(posEta),rmsNormX);

	//std::cout<<"rmsNormX: "<<rmsNormX<<std::endl;

	h2YBpixEta->Fill(TMath::Abs(posEta),medianY*10000.);
	profYBpixEta->Fill(TMath::Abs(posEta),medianY*10000.);
	profNormResYBpixEta->Fill(TMath::Abs(posEta),rmsNormY);
	
	if(posX>0){
	  hBPIXPosX->Fill(medianX);
	} else {
	  hBPIXNegX->Fill(medianX);
	}
	
	if(rDirection>0){
	  hBPIXPosR->Fill(medianX);
	} else {
	  hBPIXNegR->Fill(medianX);
	}

	if(posZ>0){
	  hBPIXPosZ->Fill(medianX);
	} else {
	  hBPIXNegZ->Fill(medianX);
	}

	if(layer==1){
	  hBPIXL1->Fill(medianX);
	} else if(layer==2){
	  hBPIXL2->Fill(medianX);
	} else if(layer==3){
	  hBPIXL3->Fill(medianX);
	}

      } else if(subDetId==2){

	profXFpixEta->Fill(TMath::Abs(posEta),medianX*10000.);  
	h2XFpixEta->Fill(TMath::Abs(posEta),medianX*10000.);  
	profNormResXFpixEta->Fill(TMath::Abs(posEta),rmsNormX);
	
	profYFpixEta->Fill(TMath::Abs(posEta),medianY*10000.);  
	h2YFpixEta->Fill(TMath::Abs(posEta),medianY*10000.);  
	profNormResYFpixEta->Fill(TMath::Abs(posEta),rmsNormY);

      }  else if(subDetId==3){             

	profTIBEta->Fill(TMath::Abs(posEta),medianX*10000.);  
	h2TIBEta->Fill(TMath::Abs(posEta),medianX*10000.);    
	profNormResTIBEta->Fill(TMath::Abs(posEta),rmsNormX);
          
      } else if(subDetId==4){      
  
	profTIDEta->Fill(TMath::Abs(posEta),medianX*10000.);  
	h2TIDEta->Fill(TMath::Abs(posEta),medianX*10000.); 
	profNormResTIDEta->Fill(TMath::Abs(posEta),rmsNormX);  
   
      }  else if(subDetId==5){

	profTOBEta->Fill(TMath::Abs(posEta),medianX*10000.);  
	h2TOBEta->Fill(TMath::Abs(posEta),medianX*10000.); 
	profNormResTOBEta->Fill(TMath::Abs(posEta),rmsNormX);
	
      } else if (subDetId==6){
                  
	profTECEta->Fill(TMath::Abs(posEta),medianX*10000.);  
	h2TECEta->Fill(TMath::Abs(posEta),medianX*10000.);   
	profNormResTECEta->Fill(TMath::Abs(posEta),rmsNormX); 
     
      }
  }
  
  setStyle("fire");
 
  // BPIX-x
  makeNiceCanv(cProfBPixRMSx_DMR_Eta);
  cProfBPixRMSx_DMR_Eta->cd();
  gPad->SetRightMargin(0.12);
  makeNice2DPlotStyle(h2XBpixEta);
  h2XBpixEta->Draw("colz");
  profXBpixEta->SetLineColor(kBlue);
  profXBpixEta->SetMarkerColor(kBlue);
  profXBpixEta->SetLineWidth(2.);
  profXBpixEta->SetMarkerStyle(20);
  profXBpixEta->SetMarkerSize(1.4);
  profXBpixEta->Draw("E1same");

  //FPIX-x
  makeNiceCanv(cProfFPixRMSx_DMR_Eta);
  gPad->SetRightMargin(0.12);
  cProfFPixRMSx_DMR_Eta->cd();
  makeNice2DPlotStyle(h2XFpixEta);
  h2XFpixEta->Draw("colz");
  profXFpixEta->SetLineColor(kBlue);
  profXFpixEta->SetMarkerColor(kBlue);
  profXFpixEta->SetLineWidth(2.);
  profXFpixEta->SetMarkerStyle(20);
  profXFpixEta->SetMarkerSize(1.4);
  profXFpixEta->Draw("E1same");

  // BPIX-y
  makeNiceCanv(cProfBPixRMSy_DMR_Eta);
  gPad->SetRightMargin(0.12);
  cProfBPixRMSy_DMR_Eta->cd();
  makeNice2DPlotStyle(h2YBpixEta);
  h2YBpixEta->Draw("colz");
  profYBpixEta->SetLineColor(kBlue);
  profYBpixEta->SetMarkerColor(kBlue);
  profYBpixEta->SetLineWidth(2.);
  profYBpixEta->SetMarkerStyle(20);
  profYBpixEta->SetMarkerSize(1.4);
  profYBpixEta->Draw("E1same");

  //FPIX-y
  makeNiceCanv(cProfFPixRMSy_DMR_Eta);
  gPad->SetRightMargin(0.12);
  cProfFPixRMSy_DMR_Eta->cd();
  makeNice2DPlotStyle(h2YFpixEta);
  h2YFpixEta->Draw("colz");
  profYFpixEta->SetLineColor(kBlue);
  profYFpixEta->SetMarkerColor(kBlue);
  profYFpixEta->SetLineWidth(2.);
  profYFpixEta->SetMarkerStyle(20);
  profYFpixEta->SetMarkerSize(1.4);
  profYFpixEta->Draw("E1same");

  //TIB
  makeNiceCanv(cProfTIBRMS_DMR_Eta);
  gPad->SetRightMargin(0.12);
  cProfTIBRMS_DMR_Eta->cd();
  makeNice2DPlotStyle(h2TIBEta);
  h2TIBEta->Draw("colz");
  profTIBEta->SetLineColor(kBlue);
  profTIBEta->SetMarkerColor(kBlue);
  profTIBEta->SetLineWidth(2.);
  profTIBEta->SetMarkerStyle(20);
  profTIBEta->SetMarkerSize(1.4);
  profTIBEta->Draw("E1same");

  //TOB
  makeNiceCanv(cProfTOBRMS_DMR_Eta);
  gPad->SetRightMargin(0.12);
  cProfTOBRMS_DMR_Eta->cd();
  makeNice2DPlotStyle(h2TOBEta);
  h2TOBEta->Draw("colz");
  profTOBEta->SetLineColor(kBlue);
  profTOBEta->SetMarkerColor(kBlue);
  profTOBEta->SetLineWidth(2.);
  profTOBEta->SetMarkerStyle(20);
  profTOBEta->SetMarkerSize(1.4);
  profTOBEta->Draw("E1same");

  //TID
  makeNiceCanv(cProfTIDRMS_DMR_Eta);
  gPad->SetRightMargin(0.12);
  cProfTIDRMS_DMR_Eta->cd();
  makeNice2DPlotStyle(h2TIDEta);
  h2TIDEta->Draw("colz");
  profTIDEta->SetLineColor(kBlue);
  profTIDEta->SetMarkerColor(kBlue);
  profTIDEta->SetLineWidth(2.);
  profTIDEta->SetMarkerStyle(20);
  profTIDEta->SetMarkerSize(1.4);
  profTIDEta->Draw("E1same");

  //TEC
  makeNiceCanv(cProfTECRMS_DMR_Eta);
  gPad->SetRightMargin(0.12);
  cProfTECRMS_DMR_Eta->cd();
  makeNice2DPlotStyle(h2TECEta);
  h2TECEta->Draw("colz");
  profTECEta->SetLineColor(kBlue);
  profTECEta->SetMarkerColor(kBlue);
  profTECEta->SetLineWidth(2.);
  profTECEta->SetMarkerStyle(20);
  profTECEta->SetMarkerSize(1.4);
  profTECEta->Draw("E1same");

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

  TLegend *leg = new TLegend(0.14,0.75,0.54,0.93);
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

  cAllRMSVsEta->SaveAs("cALLRMSVsEta.root");

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

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

  TLegend *leg2 = new TLegend(0.14,0.75,0.54,0.93);
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

  cAllRMSNormVsEta->SaveAs("cALLRMSNormVsEta.root");

  makeNiceCanv(c);
  c->cd();
  
  makeNicePlotStyle(hBPIXAll);
  hBPIXAll->Draw();
  
  //******************** X canvas 

  makeNiceCanv(cX);
  cX->cd();
  hBPIXAll->Draw();
  makeNicePlotStyleA(hBPIXPosX);
  hBPIXPosX->Draw("same");
  makeNicePlotStyleB(hBPIXNegX);
  hBPIXNegX->Draw("same");
  
  TObjArray *cxH = new TObjArray(3);
  cxH->Add(hBPIXAll);
  cxH->Add(hBPIXPosX);
  cxH->Add(hBPIXNegX);
  
  TPaveText* tt1 = addNiceTLegend(cxH);
  tt1->Draw("same");
   
  cX->SaveAs("BPIX_DMedYR_PosXNegX.pdf");
  cX->SaveAs("BPIX_DMedYR_PosXNegX.png");

  //******************** R canvas 

  makeNiceCanv(cR);
  cR->cd();
  hBPIXAll->Draw();
  makeNicePlotStyleA(hBPIXPosR);
  hBPIXPosR->Draw("same");
  makeNicePlotStyleB(hBPIXNegR);
  hBPIXNegR->Draw("same");

  TObjArray *crH = new TObjArray(3);
  crH->Add(hBPIXAll);
  crH->Add(hBPIXPosR);
  crH->Add(hBPIXNegR);
  
  TPaveText* tt2 = addNiceTLegend(crH);
  tt2->Draw("same");
  
  cR->SaveAs("BPIX_DMedYR_in_out.pdf");
  cR->SaveAs("BPIX_DMedYR_in_out.png");

  //******************** X canvas 

  makeNiceCanv(cZ);
  cZ->cd();
  hBPIXAll->Draw();
  makeNicePlotStyleA(hBPIXPosZ);
  hBPIXPosZ->Draw("same");
  makeNicePlotStyleB(hBPIXNegZ);
  hBPIXNegZ->Draw("same");
  
  TObjArray *czH = new TObjArray(3);
  czH->Add(hBPIXAll);
  czH->Add(hBPIXPosZ);
  czH->Add(hBPIXNegZ);
  
  TPaveText* tt3 = addNiceTLegend(czH);
  tt3->Draw("same");

  //******************** layer canvas 

  makeNiceCanv(cL);
  cL->cd();

  makeNicePlotStyleB(hBPIXL2);
  hBPIXL2->Draw();

  makeNicePlotStyle(hBPIXL1);
  hBPIXL1->Draw("same");

  makeNicePlotStyleA(hBPIXL3);
  hBPIXL3->Draw("same");
 
  TObjArray *clH = new TObjArray(3);
  clH->Add(hBPIXL1);
  clH->Add(hBPIXL2);
  clH->Add(hBPIXL3);
  
  TPaveText* tt4 = addNiceTLegend(clH);
  tt4->Draw("same");

  cL->SaveAs("BPIX_DMedYR_Layerwise.pdf");
  cL->SaveAs("BPIX_DMedYR_Layerwise.png");

}

