#define RunIIIPosData_cxx
#include "RunIIIPosData.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


int nEVENTS = 28963;//<---Total amount of events within sample
int nEVENTSt = 15000;//<---Amount of events to test code with

// #############################################################################
// ######################## HISTOGRAMS ARE DEFINED HERE ########################
// #############################################################################

TH1D *hNumReconstructedTracks = new TH1D("hNumReconstructedTracks", "Amount of Tracks for the Event", nEVENTS, 0, nEVENTS);

TH1D *hNumTracksPerEvent = new TH1D("hNumTracksPerEvent", "Amount of Events With Some Number of Tracks", 50, 0, 50);

TH1D *hNumWCTracks = new TH1D("hNumWCTracks", "Number of Wire Chamber Tracks", 10, 0, 5);

TH1D *hdataWCTheta = new TH1D("hdataWCTheta", "WCTrack Theta", 180, 0, 90);

TH1D *hdataWCPhi = new TH1D("hdataWCPhi", "WCTrack Phi", 360, 0, 360);

TH1D *hdataTPCTheta = new TH1D("hdataTPCTheta", "TPC Track Theta", 180, 0, 90);

TH1D *hdataTPCPhi = new TH1D("hdataTPCPhi", "TPC Track Phi", 360, 0, 360);

TH1D *hdataTrkInitialX = new TH1D("hdataTrkInitialX", "Initial X Position of the TPC Track", 100, 0, 50);

TH1D *hdataTrkInitialY = new TH1D("hdataTrkInitialY", "Initial Y Position of the TPC Track", 100, -25, 25);

TH1D *hdataNMatchTPCWCTrk = new TH1D("hdataNMatchTPCWCTrk", "Number of matched TPC/WC Tracks", 20, 0, 10);

TH1D *hdataDeltaWCTrkX = new TH1D("hdataDeltaWCTrkX", "#Delta X TPC/WC Track", 160, -40, 40);

TH1D *hdataDeltaWCTrkY = new TH1D("hdataDeltaWCTrkY", "#Delta Y TPC/WC Track", 160, -40, 40);

TH1D *hdataAlpha = new TH1D("hdataAlpha", "#alpha between WC and TPC Track", 90, 0, 90);

// #############################################################################
// ############################# END OF HISTOGRAMS #############################
// #############################################################################


void RunIIIPosData::Loop()
{
if (fChain == 0) return;
Long64_t nentries = fChain->GetEntriesFast();
Long64_t nbytes = 0, nb = 0;

// |----------------------------------------------------------|
// |--------------- Putting Flexible Cuts Here ---------------|
// |----------------------------------------------------------|


// ### Delta X Between Wire Chamber Track and TPC Track ###
double DeltaXLowerBound = -4.0;
double DeltaXUpperBound = 6.0;

// ### Delta Y Between Wire Chamber Track and TPC Track ###
double DeltaYLowerBound = -5.0;
double DeltaYUpperBound = 5.0;

// ### Fiducial Boundary Cuts (used to determine if a track is stopping) ###
double XLowerFid = 0;
double XUpperFid = 47;

double YLowerFid = -20;
double YUpperFid = 20;

double ZLowerFid = 0;
double ZUpperFid = 90;

// ### Alpha Cut in Degrees ###
double alphaCut = 10;

// ### Restriction of the Upper Part of the TPC ###
int UpperPartOfTPC = 90.0;


// |----------------------------------------------------------|
// |----------------------------------------------------------|

//std::cout<<"The Total Number of Events is:"<<nentries<<std::endl;

// ============================================
// |--- Declaring the ROOT file to save to ---|
// ============================================
TFile myfile("../histoROOTfiles_forPlots/RunIIIPosPolData_histos.root", "RECREATE");

// ==================
// |--- Counters ---|
// ==================
int nTotalEvents = 0, nEventsWCTrack = 0, nEventsTPC = 0, nEvtsWCTrackMatch = 0, nOneTPC = 0, nWCTrackReconstructed = 0;

// ===================================================
// |--- Setting an index for matched WC/TPC track ---|
// ===================================================
int MatchWCTrackIndex[10] = {0};

// =================================
// |--- Looping over all events ---|
// =================================
  for (Long64_t jentry=0; jentry<nentries; jentry++) 
//for (Long64_t jentry=0; jentry<nEVENTStesting; jentry++)
   {

   // ===========================
   // |--- Loading the event ---|
   // ===========================
   Long64_t ientry = LoadTree(jentry);
   if (ientry < 0) break;
   nb = fChain->GetEntry(jentry);   nbytes += nb;

   // =========================================================================
   // |--- Gets the number of tracks that were reconstructed in this event ---|
   // =========================================================================
   for (int i = 0; i < ntracks_reco; i++)
      {
      // ===============================================================
      // |--- Fill in the amount of tracks for this event histogram ---|
      // ===============================================================
      hNumReconstructedTracks->Fill(jentry);

      }//<---End tracks loop


   // ===============================================================================
   // |--- Fill in the amount of events with the same number of tracks histogram ---|
   // ===============================================================================
   hNumTracksPerEvent->Fill(ntracks_reco);
   hNumWCTracks->Fill(nwctrks);

   // ===============================
   // |--- Counting Total Events ---|
   // ===============================
   nTotalEvents++;

   if (nwctrks > 0) {nWCTrackReconstructed++;}
   if (nwctrks > 0 && ntracks_reco > 0) {nOneTPC++;}

   // === Outputting every nEvents to the screen ===
   if(nTotalEvents % 500 == 0){std::cout<<"Event = "<<nTotalEvents<<std::endl;}

   //=======================================================================================================================
   //                                           Uniquely matching one WC Track to TPC Track
   //=======================================================================================================================
  
   // ### Keeping track of the number of matched tracks ###
   int nMatchedTracks = 0;
  
   // ### Variables for Delta WC and TPC tracks ###
   float DeltaX_WC_TPC_Track = 999;
   float DeltaY_WC_TPC_Track = 999;
  
   // ### Setting the index for the track which is ###
   // ### uniquely matched to a wire chamber track ###
   bool MatchTPC_WVTrack[500] = {false};
  
   MatchWCTrackIndex[0] = 0;
   MatchWCTrackIndex[1] = 0;
   MatchWCTrackIndex[2] = 0;
   MatchWCTrackIndex[3] = 0;
   MatchWCTrackIndex[4] = 0;
   MatchWCTrackIndex[5] = 0;
   MatchWCTrackIndex[6] = 0;
   MatchWCTrackIndex[7] = 0;
   MatchWCTrackIndex[8] = 0;
   
   // #############################################
   // ### Loop over all the wire chamber tracks ###
   // #############################################
   for (int mwctrk = 0; mwctrk < nwctrks; mwctrk++)
      {  
      // ### Grab the WCTrack Theta ###;
      hdataWCTheta->Fill(wctrk_theta[mwctrk]* (180.0/3.141592654));
 
      // ### Grabbing the WCTrack Phi ###
      hdataWCPhi->Fill(wctrk_phi[mwctrk]* (180.0/3.141592654));
  
      // ####################################
      // ### Loop over all the TPC Tracks ###
      // ####################################
      for (int nTPCtrk = 0; nTPCtrk < ntracks_reco; nTPCtrk++)         
         {
         // === Set a dummy variables for the most upstream point ===
         float FirstSpacePointZ = 999;
         float FirstSpacePointY = 999;
         float FirstSpacePointX = 999;
  
         float TempTrj_X = 999;
         float TempTrj_Y = 999;
         float TempTrj_Z = 999;

         // ###############################################################
         // ### Looping over the trajectory points for the prelim-track ###
         // ###############################################################
         for (int ntrjpts = 0; ntrjpts < nTrajPoint[nTPCtrk]; ntrjpts++)
            {
            // ### Recording this tracks upstream most X, Y, Z location, ###
            // ###       which is inside the fiducial boundary           ###
            
            //std::cout<<trjPt_Z[nTPCtrk][ntrjpts]<<", "<<trjPt_Y[nTPCtrk][ntrjpts]<<", "<<trjPt_X[nTPCtrk][ntrjpts]<<std::endl;

            if (trjPt_Z[nTPCtrk][ntrjpts] < FirstSpacePointZ && trjPt_Y[nTPCtrk][ntrjpts] > YLowerFid && trjPt_Y[nTPCtrk][ntrjpts] < YUpperFid && trjPt_X[nTPCtrk][ntrjpts] > XLowerFid && trjPt_X[nTPCtrk][ntrjpts] < XUpperFid && trjPt_Z[nTPCtrk][ntrjpts] < UpperPartOfTPC)
               {
               // ######################################
               // ### Record the most upstream point ###
               // ######################################
               FirstSpacePointZ = trjPt_Z[nTPCtrk][ntrjpts];
               FirstSpacePointY = trjPt_Y[nTPCtrk][ntrjpts];
               FirstSpacePointX = trjPt_X[nTPCtrk][ntrjpts];

               TempTrj_X = pHat0_X[nTPCtrk][ntrjpts];
               TempTrj_Y = pHat0_Y[nTPCtrk][ntrjpts];
               TempTrj_Z = pHat0_Z[nTPCtrk][ntrjpts];
               }//<---End finding the most upstream point


            }//<---End ntrjpts loop


         // ###################################################
         // ### Vectors for angles between TPC and WC Track ###
         // ###################################################
         TVector3 z_hat(0,0,1);
         TVector3 p_hat_0;
       
         // ### Setting the vector for the matched track ###
         // ###      most upstream trajectory point      ###
         p_hat_0.SetX(TempTrj_X);
         p_hat_0.SetY(TempTrj_Y);
         p_hat_0.SetZ(TempTrj_Z); //<--Note: since at this point we only have one unique match
                                  //         only having one entry should be fine
                                                                                                                                                  // ===============================================================================================================
         //                             Calculating Theta and Phi for this TPC Track
         // ===============================================================================================================
         // ### Calculating the Theta for the TPC Track ###
         float tpcTheta = acos(z_hat.Dot(p_hat_0)/p_hat_0.Mag());
         hdataTPCTheta->Fill(tpcTheta* (180.0/3.141592654));
        
         // ### Using same convention as WCTrack to calculate phi ###
         float phi = 0;
         //Calculating phi (degeneracy elimination for the atan function)
         //----------------------------------------------------------------------------------------------
         if( p_hat_0.Y() > 0 && p_hat_0.X() > 0 ){ phi = atan(p_hat_0.Y()/p_hat_0.X()); }
         else if( p_hat_0.Y() > 0 && p_hat_0.X() < 0 ){ phi = atan(p_hat_0.Y()/p_hat_0.X())+3.141592654; }
         else if( p_hat_0.Y() < 0 && p_hat_0.X() < 0 ){ phi = atan(p_hat_0.Y()/p_hat_0.X())+3.141592654; }
         else if( p_hat_0.Y() < 0 && p_hat_0.X() > 0 ){ phi = atan(p_hat_0.Y()/p_hat_0.X())+6.28318; }
         else if( p_hat_0.Y() == 0 && p_hat_0.X() == 0 ){ phi = 0; }//defined by convention
         else if( p_hat_0.Y() == 0 )
            {
            if( p_hat_0.X() > 0 ){ phi = 0; }

            else{ phi = 3.141592654; }

            }
         else if( p_hat_0.X() == 0 )
            {
            if( p_hat_0.Y() > 0 ){ phi = 3.141592654/2; }
            else{ phi = 3.141592654*3/2; }

            }
         //----------------------------------------------------------------------------------------------
         
         // ### Using TPC Phi ###
         float tpcPhi = phi;
         hdataTPCPhi->Fill(tpcPhi* (180.0/3.141592654));

         // ===============================================================================================================
         // ===============================================================================================================

         // #######################################################
         // ### Defining unit vectors for the WC and TPC tracks ###
         // #######################################################
         TVector3 theUnitVector_WCTrack;
         TVector3 theUnitVector_TPCTrack;

         // === WCTrack Unit Vector ===
         theUnitVector_WCTrack.SetX(sin(wctrk_theta[mwctrk])*cos(wctrk_phi[mwctrk]));
         theUnitVector_WCTrack.SetY(sin(wctrk_theta[mwctrk])*sin(wctrk_phi[mwctrk]));
         theUnitVector_WCTrack.SetZ(cos(wctrk_theta[mwctrk]));

         // === TPC Track Unit Vector ===
         theUnitVector_TPCTrack.SetX(sin(tpcTheta)*cos(tpcPhi));
         theUnitVector_TPCTrack.SetY(sin(tpcTheta)*sin(tpcPhi));
         theUnitVector_TPCTrack.SetZ(cos(tpcTheta));

         // ##########################################################################
         // ### Calculating the Delta X and Delta Y between WC track and TPC track ###
         // ##########################################################################
         DeltaX_WC_TPC_Track = FirstSpacePointX - (wctrk_XFaceCoor[mwctrk]);//<---Note we multiply by 0.1 to convert to centimeters
         DeltaY_WC_TPC_Track = FirstSpacePointY - (wctrk_YFaceCoor[mwctrk]);//<---Note we multiply by 0.1 to convert to centimeters

         //std::cout<<FirstSpacePointX<<", "<<wctrk_XFaceCoor[mwctrk]<<", "<<FirstSpacePointY<<", "<<wctrk_YFaceCoor[mwctrk]<<std::endl;

         // ### Filling the tracks initial X and Y position ###
         hdataTrkInitialX->Fill(FirstSpacePointX);
         hdataTrkInitialY->Fill(FirstSpacePointY);


         // ###########################################################
         // ### Calculating the angle between WCTrack and TPC Track ###
         // ###########################################################
         float alpha = ( acos(theUnitVector_WCTrack.Dot(theUnitVector_TPCTrack)) )* (180.0/3.141592654);


         // ### Filling the Delta X and Delta Y  and alpha between WC tracks and TPC Tracks ###
         hdataDeltaWCTrkY->Fill(DeltaY_WC_TPC_Track);
         hdataDeltaWCTrkX->Fill(DeltaX_WC_TPC_Track);
         hdataAlpha->Fill(alpha);

         // ###########################################################################
         // ### If this TPC track matches this Wire Chamber Track, bump the counter ###
         // ###########################################################################
         if ( DeltaX_WC_TPC_Track >  DeltaXLowerBound && DeltaX_WC_TPC_Track < DeltaXUpperBound && DeltaY_WC_TPC_Track > DeltaYLowerBound && DeltaY_WC_TPC_Track < DeltaYUpperBound && alpha < alphaCut )
            {
            // ### Counting the matched tracks ###
            nMatchedTracks++;

            // ### Setting the index of this track to true ###
            MatchTPC_WVTrack[nTPCtrk] = true;

            // ### Setting the WCTrack Index = 1 if this WCTrack was matched ###
            MatchWCTrackIndex[mwctrk] = 1;
            }


         }//<---End nTPCtrk loop


      }//<---End loop over wire chamber tracks


   // ### Filling the number of matched WC and TPC Tracks ###
   hdataNMatchTPCWCTrk->Fill(nMatchedTracks);

   }//<---End events loop


std::cout<<"Total number of events in the AnaModule is: "<<nTotalEvents<<std::endl;
std::cout<<"Number of events with a Wire Chamber track reconstructed: "<<nWCTrackReconstructed<<std::endl;
std::cout<<"Number of events with at least 1 TPC track reconstructed: "<<nOneTPC<<std::endl;

// =================================
// |--- Plotting the histograms ---|
// =================================
TCanvas *c1 = new TCanvas("c1", "Number of Tracks Reconstructed for that Event");
c1->SetTicks();
c1->SetFillColor(kWhite);
hNumReconstructedTracks->GetXaxis()->SetTitle("Event Number");
hNumReconstructedTracks->GetXaxis()->CenterTitle();
hNumReconstructedTracks->GetYaxis()->SetTitle("Number of Tracks Reconstructed");
hNumReconstructedTracks->GetYaxis()->CenterTitle();
hNumReconstructedTracks->SetLineColor(kBlue);
hNumReconstructedTracks->Draw();

TCanvas *c2 = new TCanvas("c2", "Number of Events With the Same Amount of Reconstructed Tracks");
c2->SetTicks();
c2->SetFillColor(kWhite);
hNumTracksPerEvent->GetXaxis()->SetTitle("Number of Reconstructed Tracks");
hNumTracksPerEvent->GetXaxis()->CenterTitle();
hNumTracksPerEvent->GetYaxis()->SetTitle("Number of Events With Same Amount of Tracks Reconstructed");
hNumTracksPerEvent->GetYaxis()->CenterTitle();
hNumTracksPerEvent->SetLineColor(kBlue);
hNumTracksPerEvent->Draw();

TCanvas *c3 = new TCanvas("c3", "Delta X");
c3->SetTicks();
c3->SetFillColor(kWhite);
hdataDeltaWCTrkX->GetXaxis()->SetTitle("Delta X (cm)");
hdataDeltaWCTrkX->GetXaxis()->CenterTitle();
hdataDeltaWCTrkX->GetYaxis()->SetTitle("Events/DeltaX (#/cm)");
hdataDeltaWCTrkX->GetYaxis()->CenterTitle();
hdataDeltaWCTrkX->SetLineColor(kBlue);
hdataDeltaWCTrkX->Draw();

TCanvas *c4 = new TCanvas("c4", "Delta Y");
c4->SetTicks();
c4->SetFillColor(kWhite);
hdataDeltaWCTrkY->GetXaxis()->SetTitle("Delta Y (cm)");
hdataDeltaWCTrkY->GetXaxis()->CenterTitle();
hdataDeltaWCTrkY->GetYaxis()->SetTitle("Events/DeltaY (#/cm");
hdataDeltaWCTrkY->GetYaxis()->CenterTitle();
hdataDeltaWCTrkY->SetLineColor(kBlue);
hdataDeltaWCTrkY->Draw();

TCanvas *c5 = new TCanvas("c5", "Alpha");
c5->SetTicks();
c5->SetFillColor(kWhite);
hdataAlpha->GetXaxis()->SetTitle("Alpha Angle (Degrees)");
hdataAlpha->GetXaxis()->CenterTitle();
hdataAlpha->GetYaxis()->SetTitle("Events/Degrees (#/Degrees)");
hdataAlpha->GetYaxis()->CenterTitle();
hdataAlpha->SetLineColor(kBlue);
hdataAlpha->Draw();

TCanvas *c6 = new TCanvas("c6", "Matched Wire Chamber to TPC Tracks Events");
c6->SetTicks();
c6->SetFillColor(kWhite);
hdataNMatchTPCWCTrk->GetXaxis()->SetTitle("Num WC/TPC Matched Tracks");
hdataNMatchTPCWCTrk->GetXaxis()->CenterTitle();
hdataNMatchTPCWCTrk->GetYaxis()->SetTitle("Events");
hdataNMatchTPCWCTrk->GetYaxis()->CenterTitle();
hdataNMatchTPCWCTrk->SetLineColor(kBlue);
hdataNMatchTPCWCTrk->Draw();

TCanvas *c7 = new TCanvas("c7", "Wire Chamber Tracks");
c7->SetTicks();
c7->SetFillColor(kWhite);
hNumWCTracks->GetXaxis()->SetTitle("Num Events With Same Amount of Tracks");
hNumWCTracks->GetXaxis()->CenterTitle();
hNumWCTracks->GetYaxis()->SetTitle("Amount of WC Tracks");
hNumWCTracks->GetYaxis()->CenterTitle();
hNumWCTracks->SetLineColor(kBlue);
hNumWCTracks->Draw();


// =====================================================
// |--- Writing out the histograms to the ROOT file ---|
// =====================================================
hNumReconstructedTracks->Write();
hNumTracksPerEvent->Write();

hdataTPCTheta->Write();
hdataTPCPhi->Write();

hdataWCTheta->Write();
hdataWCPhi->Write();

hdataTrkInitialX->Write();
hdataTrkInitialY->Write();

hdataDeltaWCTrkY->Write();
hdataDeltaWCTrkX->Write();
hdataAlpha->Write();

hdataNMatchTPCWCTrk->Write();

hNumWCTracks->Write();

}//<---End void loop
