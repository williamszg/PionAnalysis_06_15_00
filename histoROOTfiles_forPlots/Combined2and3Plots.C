{
// ======================================================================================
// |--------------------------------- Read in the Data ---------------------------------|
// ======================================================================================

// ######################################################################################
// ##################### Loading and Setting Up Histograms for Run-II ###################
// ######################################################################################

TFile *f1 = new TFile("RunIIPosPolData_histos.root"); //Load the histograms for Run-II

TH1D *hNumWCTracks2 = (TH1D*)f1->Get("hNumWCTracks");
TH1D *hNumTracksPerEvent2 = (TH1D*)f1->Get("hNumTracksPerEvent");
TH1D *hdataDeltaWCTrkX2 = (TH1D*)f1->Get("hdataDeltaWCTrkX");
TH1D *hdataDeltaWCTrkY2 = (TH1D*)f1->Get("hdataDeltaWCTrkY");
TH1D *hdataAlpha2 = (TH1D*)f1->Get("hdataAlpha");

hNumWCTracks2->Sumw2();
hNumTracksPerEvent2->Sumw2();
hdataDeltaWCTrkX2->Sumw2();
hdataDeltaWCTrkY2->Sumw2();
hdataAlpha2->Sumw2();

// ######################################################################################
// ######################################################################################




// ######################################################################################
// #################### Loading and Setting Up Histograms for Run-III ###################
// ######################################################################################

TFile *f2 = new TFile("RunIIIPosPolData_histos.root"); //Load the histograms for Run-III

TH1D *hNumWCTracks3 = (TH1D*)f2->Get("hNumWCTracks");
TH1D *hNumTracksPerEvent3 = (TH1D*)f2->Get("hNumTracksPerEvent");
TH1D *hdataDeltaWCTrkX3 = (TH1D*)f2->Get("hdataDeltaWCTrkX");
TH1D *hdataDeltaWCTrkY3 = (TH1D*)f2->Get("hdataDeltaWCTrkY");
TH1D *hdataAlpha3 = (TH1D*)f2->Get("hdataAlpha");

hNumWCTracks3->Sumw2();
hNumTracksPerEvent3->Sumw2();
hdataDeltaWCTrkX3->Sumw2();
hdataDeltaWCTrkY3->Sumw2();
hdataAlpha3->Sumw2();

// ######################################################################################
// ######################################################################################

// ======================================================================================
// ======================================================================================




// ======================================================================================
// |------------------------------- Making the Plots -----------------------------------|
// ======================================================================================

// ######################################################################################
// ################################# Some Histogram #####################################
// ######################################################################################
TCanvas *c1 = new TCanvas("c1", "Blah");
c1->SetTicks();
c1->SetFillColor(kWhite);

// |--- Area Normalizing the Plot ---|
hNumWCTracks2->Scale(1/hNumWCTracks2->Integral());
hNumWCTracks3->Scale(1/hNumWCTracks3->Integral());

hNumWCTracks2->SetLineColor(kBlue);
hNumWCTracks2->SetLineWidth(2);

hNumWCTracks3->SetLineColor(kRed);
hNumWCTracks3->SetLineWidth(2);

hNumWCTracks3->GetXaxis()->SetTitle("Number of WC Tracks");
hNumWCTracks3->GetXaxis()->CenterTitle();

hNumWCTracks3->GetYaxis()->SetTitle("Normalized Events");
hNumWCTracks3->GetYaxis()->CenterTitle();

hNumWCTracks3->Draw("histo");
hNumWCTracks2->Draw("histosame");


// |--- Defining the Legend for the Plot ---|
TLegend *leg1 = new TLegend();
leg1 = new TLegend(0.58,0.65,0.88,0.88);
leg1->SetTextSize(0.04);
leg1->SetTextAlign(12);
leg1->SetFillColor(kWhite);
leg1->SetLineColor(kWhite);
leg1->SetShadowColor(kWhite);
leg1->SetHeader("First Look at Run-III");
leg1->AddEntry(hNumWCTracks2,"Run-II");
leg1->AddEntry(hNumWCTracks3,"Run-III");
leg1->Draw();
// ######################################################################################
// ######################################################################################




// ######################################################################################
// ################################# Some Histogram #####################################
// ######################################################################################
TCanvas *c2 = new TCanvas("c2", "Blah");
c2->SetTicks();
c2->SetFillColor(kWhite);

// |--- Area Normalizing the Plot ---|
hNumTracksPerEvent2->Scale(1/hNumTracksPerEvent2->Integral());
hNumTracksPerEvent3->Scale(1/hNumTracksPerEvent3->Integral());

hNumTracksPerEvent2->SetLineColor(kBlue);
hNumTracksPerEvent2->SetLineWidth(2);

hNumTracksPerEvent3->SetLineColor(kRed);
hNumTracksPerEvent3->SetLineWidth(2);

hNumTracksPerEvent3->GetXaxis()->SetTitle("Number of Tracks");
hNumTracksPerEvent3->GetXaxis()->CenterTitle();

hNumTracksPerEvent3->GetYaxis()->SetTitle("Normalized Events");
hNumTracksPerEvent3->GetYaxis()->CenterTitle();

hNumTracksPerEvent3->Draw("histo");
hNumTracksPerEvent2->Draw("histosame");


// |--- Defining the Legend for the Plot ---|
TLegend *leg2 = new TLegend();
leg2 = new TLegend(0.58,0.65,0.88,0.88);
leg2->SetTextSize(0.04);
leg2->SetTextAlign(12);
leg2->SetFillColor(kWhite);
leg2->SetLineColor(kWhite);
leg2->SetShadowColor(kWhite);
leg2->SetHeader("First Look at Run-III");
leg2->AddEntry(hNumTracksPerEvent2,"Run-II");
leg2->AddEntry(hNumTracksPerEvent3,"Run-III");
leg2->Draw();
// ######################################################################################
// ######################################################################################




// ######################################################################################
// ################################# Some Histogram #####################################
// ######################################################################################
TCanvas *c3 = new TCanvas("c3", "Blah");
c3->SetTicks();
c3->SetFillColor(kWhite);

// |--- Area Normalizing the Plot ---|
hdataDeltaWCTrkX2->Scale(1/hdataDeltaWCTrkX2->Integral());
hdataDeltaWCTrkX3->Scale(1/hdataDeltaWCTrkX3->Integral());

hdataDeltaWCTrkX2->SetLineColor(kBlue);
hdataDeltaWCTrkX2->SetLineWidth(2);

hdataDeltaWCTrkX3->SetLineColor(kRed);
hdataDeltaWCTrkX3->SetLineWidth(2);

hdataDeltaWCTrkX3->GetXaxis()->SetTitle("Change in X Between WC and TPC (cm)");
hdataDeltaWCTrkX3->GetXaxis()->CenterTitle();

hdataDeltaWCTrkX3->GetYaxis()->SetTitle("Normalized Events");
hdataDeltaWCTrkX3->GetYaxis()->CenterTitle();

hdataDeltaWCTrkX3->Draw("histo");
hdataDeltaWCTrkX2->Draw("histosame");


// |--- Defining the Legend for the Plot ---|
TLegend *leg3 = new TLegend();
leg3 = new TLegend(0.58,0.65,0.88,0.88);
leg3->SetTextSize(0.04);
leg3->SetTextAlign(12);
leg3->SetFillColor(kWhite);
leg3->SetLineColor(kWhite);
leg3->SetShadowColor(kWhite);
leg3->SetHeader("First Look at Run-III");
leg3->AddEntry(hdataDeltaWCTrkX2,"Run-II");
leg3->AddEntry(hdataDeltaWCTrkX3,"Run-III");
leg3->Draw();
// ######################################################################################
// ######################################################################################




// ######################################################################################
// ################################# Some Histogram #####################################
// ######################################################################################
TCanvas *c4 = new TCanvas("c4", "Blah");
c4->SetTicks();
c4->SetFillColor(kWhite);

// |--- Area Normalizing the Plot ---|
hdataDeltaWCTrkY2->Scale(1/hdataDeltaWCTrkY2->Integral());
hdataDeltaWCTrkY3->Scale(1/hdataDeltaWCTrkY3->Integral());

hdataDeltaWCTrkY2->SetLineColor(kBlue);
hdataDeltaWCTrkY2->SetLineWidth(2);

hdataDeltaWCTrkY3->SetLineColor(kRed);
hdataDeltaWCTrkY3->SetLineWidth(2);

hdataDeltaWCTrkY3->GetXaxis()->SetTitle("Change in Y Between WC and TPC (cm)");
hdataDeltaWCTrkY3->GetXaxis()->CenterTitle();

hdataDeltaWCTrkY3->GetYaxis()->SetTitle("Normalized Events");
hdataDeltaWCTrkY3->GetYaxis()->CenterTitle();

hdataDeltaWCTrkY3->Draw("histo");
hdataDeltaWCTrkY2->Draw("histosame");


// |--- Defining the Legend for the Plot ---|
TLegend *leg4 = new TLegend();
leg4 = new TLegend(0.58,0.65,0.88,0.88);
leg4->SetTextSize(0.04);
leg4->SetTextAlign(12);
leg4->SetFillColor(kWhite);
leg4->SetLineColor(kWhite);
leg4->SetShadowColor(kWhite);
leg4->SetHeader("First Look at Run-III");
leg4->AddEntry(hdataDeltaWCTrkY2,"Run-II");
leg4->AddEntry(hdataDeltaWCTrkY3,"Run-III");
leg4->Draw();
// ######################################################################################
// ######################################################################################




// ######################################################################################
// ################################# Some Histogram #####################################
// ######################################################################################
TCanvas *c5 = new TCanvas("c5", "Blah");
c5->SetTicks();
c5->SetFillColor(kWhite);

// |--- Area Normalizing the Plot ---|
hdataAlpha2->Scale(1/hdataAlpha2->Integral());
hdataAlpha3->Scale(1/hdataAlpha3->Integral());

hdataAlpha2->SetLineColor(kBlue);
hdataAlpha2->SetLineWidth(2);

hdataAlpha3->SetLineColor(kRed);
hdataAlpha3->SetLineWidth(2);

hdataAlpha3->GetXaxis()->SetTitle("Angle Between WC and TPC (Degrees)");
hdataAlpha3->GetXaxis()->CenterTitle();

hdataAlpha3->GetYaxis()->SetTitle("Normalized Events");
hdataAlpha3->GetYaxis()->CenterTitle();

hdataAlpha3->Draw("histo");
hdataAlpha2->Draw("histosame");


// |--- Defining the Legend for the Plot ---|
TLegend *leg5 = new TLegend();
leg5 = new TLegend(0.58,0.65,0.88,0.88);
leg5->SetTextSize(0.04);
leg5->SetTextAlign(12);
leg5->SetFillColor(kWhite);
leg5->SetLineColor(kWhite);
leg5->SetShadowColor(kWhite);
leg5->SetHeader("First Look at Run-III");
leg5->AddEntry(hdataAlpha2,"Run-II");
leg5->AddEntry(hdataAlpha3,"Run-III");
leg5->Draw();
// ######################################################################################
// ######################################################################################

// ======================================================================================
// ======================================================================================
}
