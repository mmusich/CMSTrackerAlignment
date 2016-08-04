#include "TKey.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TList.h"
#include "TMath.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TObject.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include <Riostream.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TFile.h>
#include <TH1D.h>
#include <THStack.h>
#include <TLegend.h>
#include <TPaveStats.h>
#include <TPaveText.h>
#include <TString.h>
#include <TStyle.h>
#include <TText.h>
#include <iomanip>
#include <iostream>
#include <stdio.h>

TString prepareString(const char *dirname, const char *ext)
{

  TString FilesList[10];
  TString LabelsList[10];

  TString outputString="";
  Int_t nfiles=0;

  TSystemDirectory dir(dirname, dirname);
  TList *files = dir.GetListOfFiles();
  if (files) {
    TSystemFile *file;
    TString fname;
    TIter next(files);
    while ((file=(TSystemFile*)next())) {
      fname = file->GetName();
      if (!file->IsDirectory() && fname.EndsWith(ext) && fname.BeginsWith("TrackerOfflineValidationStandalone")) {
	cout <<"nfiles: "<< nfiles << " adding file: "<< fname.Data() << endl;
	FilesList[nfiles]=fname;
	TObjArray *all = fname.Tokenize(".");
	for (Int_t i = 0; i < all->GetEntries(); ++i) {
	  TString chunk = all->At(i)->GetName();
	  if (chunk.Contains("TrackerOfflineValidationStandalone")){
	    chunk.ReplaceAll("TrackerOfflineValidationStandalone_","");
	    chunk.ReplaceAll("_"," ");
	    LabelsList[nfiles]=chunk;
	  } // if .root in chunk
	} // loop on chunks in file name
	nfiles++;
      } // if correct file
    }
  }

  for(Int_t i=0;i<nfiles;i++){
    TString filestring  = FilesList[i];
    TString labelstring = LabelsList[i];
    outputString.Append(filestring);
    outputString.Append("=");
    outputString.Append(labelstring);
    if (i!=nfiles-1){
      outputString.Append(",");
    }
  }
  
  cout << "the Output String is: "<<outputString<<endl;

  return outputString;

}
