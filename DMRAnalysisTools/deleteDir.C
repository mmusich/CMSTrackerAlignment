{
  TString pwd(gSystem->pwd());
  TSystemDirectory directory("plots_DATA_2012D_new_CPE", "plots_DATA_2012D_new_CPE");
  TList *l;
  l = directory.GetListOfFiles();
  if (l) {
    l->Print();
    delete l;
  }
  directory.Delete()
  // gSystem->cd(pwd.Data());
  // l = directory.GetListOfFiles();
  // if (l) {l->Print(); delete l;}
  // gSystem->cd(pwd.Data());
  // l = directory.GetListOfFiles();
  // if (l) {l->Print(); delete l;}
  // gSystem->cd(pwd.Data());
}
