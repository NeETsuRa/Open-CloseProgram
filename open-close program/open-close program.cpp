

#include "stdafx.h"
#include <windows.h>
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;

int main( int argc, char *argv[] ) {

  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory( &si, sizeof(si) );
  si.cb = sizeof(si);
  ZeroMemory( &pi, sizeof(pi) );

	fstream log ("log.txt", fstream::app|fstream::in);
	fstream stDokInPonov("dokpon.txt", fstream::app);
	fstream lokacijeProgramov("prog.txt", fstream::app);
	fstream Dokumenti("doku.txt", fstream::app);
	fstream casiPikaza("cas.txt", fstream::app);
  stDokInPonov.close();
  lokacijeProgramov.close();
  Dokumenti.close();
  casiPikaza.close();

  //sistemski èas
	time_t t = time(0); 
    struct tm * now = localtime( & t );
	cout << "Ttrenutni datum in èas: " << endl 
		<< now->tm_mday << "." << now->tm_mon+1 << "."  << now->tm_year+1900 << endl
		<< (now->tm_hour) << ":" <<(now->tm_min) << ":"  << (now->tm_sec) << endl;
	log << "Datum in èas vnosa: " << endl 
		<< now->tm_mday << "." << now->tm_mon+1 << "."  << now->tm_year+1900 << endl
		<< (now->tm_hour) << ":" <<(now->tm_min) << ":"  << (now->tm_sec) << endl << endl;

	// Vse spremenljivke ki oblikujejo program
	string lokacija = argv[0];
	lokacija.erase(lokacija.size()-23,lokacija.size());
	cout << "Lokacija programa: " << lokacija << endl;
	log <<  "Lokacija programa: " << lokacija << endl;
	int stDok; // spremenlivka ki drži število prebranih dokumentov
	string *dokumenti;// Polje lokacij dokumentov
	int *cas; // Polje èasov prikaza dokumentov
	long time=0; // Èas izvajanja programa
	int dolzinaSeznama; //dolžina prikaza enega kroga dokumentov
	string program; //v primeru enega programa je a vpisan tu
	bool prog; // spremenljivka ki pove ali je en program (true) ali veè (false)
	string *programi;// èe je veè programov polje ki shranilokacije vseh
	int ponovitve; // število ponovitev celotnega programa

	if (argc<2){
	cout << "Rocni vnos ali vnos preko datotek? [DA/NE] ";
	cin >> program;
	   while (true){
		   if (program=="DA")
				break;
			if (program=="NE")
				break;
	  
			cout << "Roèni vnos (vpisi DA) ali vnos preko datotek (vpisi NE): ";
			program.clear();
			cin >> program;
			cout << endl;
	  }
	}
	   if (program=="NE"||argc>=2){
			stDokInPonov.open("dokpon.txt");
			lokacijeProgramov.open("prog.txt");
			Dokumenti.open("doku.txt");
			casiPikaza.open("cas.txt");
		   log << "VNOS PREKO DATOTEK" << endl;
		   int odlocitev;
		   string stevilo;
		   getline (stDokInPonov, stevilo);
		   stDok=atoi(stevilo.c_str());
		   log << "stDok: " << stDok << endl;
		   stevilo.empty();
		   cas=new int [stDok];
		   dokumenti=new string [stDok];
		   getline (stDokInPonov, stevilo);
		   ponovitve=atoi(stevilo.c_str());
		   log << "ponovitve: " << ponovitve << endl;
		   stevilo.empty();
		   getline (lokacijeProgramov, stevilo);
		   odlocitev=atoi(stevilo.c_str());
		   log << "odlocitev: " << odlocitev << endl;
		   stevilo.empty();
		   if (odlocitev==1){
			   prog=true;
			   getline (lokacijeProgramov, program);
			   for (int j=0; j<program.length(); j++){
					  if(program[j]=='\\'){
						  program.insert(j,"\\");
						  j++;
					  }
				  }
		   }
		   log << "program: " << program << endl;
		   if (odlocitev==2){
			   prog=false;
				programi=new string [stDok];
				for (int i=0; i<stDok; i++){
					getline (lokacijeProgramov, programi[i]);
					log << "programi: " << programi[i] << endl;
				  }
				for (int i=0; i<stDok; i++){
				  for (int j=0; j<programi[i].length(); j++){
					  if(programi[i][j]=='\\'){
						  programi[i].insert(j,"\\");
						  j++;
					  }
				  }
				  log << "dokumenti(dvojne): " << programi[i] << endl;
			  }
			  }
		   
		   for (int i=0; i<stDok; i++){
				getline (Dokumenti, dokumenti[i]);
				log << "dokumenti: " << dokumenti[i] << endl;
			   }
		   for (int i=0; i<stDok; i++){
				getline (casiPikaza, stevilo);
				cas[i]=atoi(stevilo.c_str());
				log << "cas: " << cas[i] << endl;
				stevilo.empty();
			   }
			
			for (int i=0; i<stDok; i++){
				  for (int j=0; j<dokumenti[i].length(); j++){
					  if(dokumenti[i][j]=='\\'){
						  dokumenti[i].insert(j,"\\");
						  j++;
					  }
				  }
				  log << "dokumenti(dvojne): " << dokumenti[i] << endl;
			  }
			
			

		
		   
	   }else{
		   //priprava datotek
				stDokInPonov.open("dokpon.txt");
				lokacijeProgramov.open("prog.txt");
				Dokumenti.open("doku.txt");
				casiPikaza.open("cas.txt");

			//prièetek obdelave
			  log << "ROÈNI VNOS" << endl;
			  cout << "Vpisi stevilo dokumentov: " ;
			  cin >> stDok;
			  stDokInPonov << stDok << endl;
			  cout << endl;
			  dokumenti = new string [stDok];
			  cas = new int [stDok];
			  log << "Število dokumentov: " << stDok << endl;
			  cout << "Zagon s samo enim programom? [DA/NE]: ";
			  cin >> program;
			   while (true){
				   if (program=="DA")
						break;
					if (program=="NE")
						break;
			  
					cout << "Zagon s samo enim programom (vpiši DA) zagon s razliènimi programi (vpiši NE)";
					program.clear();
					cin >> program;
					cout << endl;
			  }
			   if (program=="DA"){
				   prog=true;
				   cout << "Vnesi pot do programske datoteke .exe" << endl;
				   lokacijeProgramov << 1 << endl;
				   program.clear();
				   cin >> program;
				   lokacijeProgramov << program << endl;
				   for (int j=0; j<program.length(); j++){
					  if(program[j]=='\\'){
						  program.insert(j,"\\");
						  j++;
					  }
				  }
			   }else{
				   prog=false;
				   lokacijeProgramov << 2 << endl;
				   programi = new string [stDok];
			   }

			  // vpis dokumentov
			  for (int i=0; i<stDok; i++){
				  cout << "Vpisi ime dokumenta (" << i+1 << ") - vpisi celotno pot (pod do programa krajsamo z IS):" << endl;
				  cin >> dokumenti[i];
				  if (dokumenti[i][0]=='I' && dokumenti[i][1]=='S'){
					  dokumenti[i].erase(0,2);
					  dokumenti[i].insert(0,lokacija);
				  }
				  cout << "koliko casa naj bo prikazano (min): ";
				  cin >> cas[i];
				  cout << endl;
				  Dokumenti << dokumenti[i] << endl;;
				  casiPikaza << cas[i] << endl;
				  log << "Dokument po vrsti: " << i << endl << "Lokacija: " << dokumenti[i] << endl <<
					  "Èas prikaza: " << cas[i] << " minut" << endl;
				  if(prog==false){
					  cout << "Vnesi pot do programske datoteke .exe" << endl;
					  cin >> programi[i];
					  cout << endl;
					  lokacijeProgramov << programi[i] << endl;
					  log << "Program za izvajanje se nahaja: " << programi[i] << endl;
				  }
			  }
			  log<< endl;

			  for (int i=0; i<stDok; i++){
				  for (int j=0; j<dokumenti[i].length(); j++){
					  if(dokumenti[i][j]=='\\'){
						  dokumenti[i].insert(j,"\\");
						  j++;
					  }
				  }
			  }
		if(prog==false)
			  for (int i=0; i<stDok; i++){
				  for (int j=0; j<programi[i].length(); j++){
					  if(programi[i][j]=='\\'){
						  programi[i].insert(j,"\\");
						  j++;
					  }
				  }
			  }

			  cout << "Zelis nastaviti stevilo ponovitev (vpisi ST) ali cas predvajanja (vpisi T): ";
			  string odlocitev;
			  cin >> odlocitev;
			  cout << endl;
			  while (true){
				   if (odlocitev=="ST")
						break;
			  
					if (odlocitev=="T")
						break;
			  
					cout << "Vpisi T za nastavitev casa predvajanja ali ST za stevilo ponovitev: ";
					odlocitev.clear();
					cin >> odlocitev;
					cout << endl;
			  }
			  dolzinaSeznama=0;
			  for (int i=0; i<stDok; i++){
					  dolzinaSeznama+=cas[i];
				  }
			  if (odlocitev=="ST"){
				  cout << "Kolikokrat se naj vse skupaj ponovi: ";
				  cin >> ponovitve;
				  cout << endl;
			  }else {
				  cout << "Koliko casa se naj ponavlja (ur): ";
				  int ure;
				  cin >> ure;
				  ure*=60;
				  ponovitve=int(ure/dolzinaSeznama);

			  }
			  stDokInPonov << ponovitve << endl;
			  log << "Stevilo ponovitev: " << ponovitve << endl << "Èas predvajanja: " <<
				  dolzinaSeznama*ponovitve << " minut" << endl << endl;
}
  // glavna zanka
  for (int j=0; j<ponovitve; j++){ //kolikokrat se mora ponovit
	  for (int i=0; i<stDok; i++){ //vsak dokument v seznamu
		cout << dokumenti[i] << endl;
		  // izgradnja komande.
		 // wstring app = L"D:\\eclipse\\eclipse.exe ";
		wstring applet;   
		if (prog==false){
			wstring app (programi[i].begin(), programi[i].end());
			applet=app;
		}else{
			wstring app (program.begin(), program.end());
			applet=app;
		}
		 // wstring kaj = L"C:\\Users\\TOSHIBA\\Desktop\\primer.bat";
		  wstring kaj (dokumenti[i].begin(), dokumenti[i].end());
		  wstring presledek = L" ";
		  
		 wstring str_command = applet + presledek + kaj; 
		  wchar_t* command = const_cast<wchar_t*>( str_command.c_str() );

		  // Odpiranje okna. 
		  if( !CreateProcess( NULL,   // ni imena modula
			  command,        // kaj in s èim
			  NULL,           // ne potrebujemo handla
			  NULL,           // Ni nitenja
			  FALSE,          // izklopljen handle
			  0,              // brez zastavic
			  NULL,           // zažene kot glavni proces
			  NULL,           // uporaba starševske lokacije 
			  &si,            // kazalec na informacije o sistemu
			  &pi )           // pointer o informacijah o programu
		  ) {
			cout << "Ni uspelo ustvariti procesa: " << GetLastError()<< endl
				<< "Napaka se je pojavila po casu " << time << " minut"<< endl;
			log << "Ni uspelo ustvariti procesa: " << GetLastError()<< endl
				<< "Napaka se je pojavila po casu " << time << " minut"<< endl;
			continue;
		  }

		  cout  <<  "odprto okno" << endl;

		  // èakanje.
		  time+=cas[i];
		  Sleep((cas[i]*60000));

		  cout  <<  "Zapiranje " << endl;;

		  // Zapiranje.
		  HANDLE explorer = OpenProcess(PROCESS_TERMINATE, false, pi.dwProcessId);
		  if( !explorer ) {
			cout << "odpiranje procesa ni uspelo: " << GetLastError()<< endl
				<< "Napaka se je pojavila po casu " << time << " minut"<< endl;
			log << "odpiranje procesa ni uspelo: " << GetLastError() << endl
				<< "Napaka se je pojavila po casu " << time << " minut"<< endl;
			
			continue;
		  }
		  if( !TerminateProcess( explorer, 0 ) ) {
			cout << "konèevanje procesa spodletelo: " << GetLastError() << endl
				<< "Napaka se je pojavila po casu " << time << " minut"<< endl;
			log << "konèevanje procesa spodletelo: " << GetLastError() << endl
				<< "Napaka se je pojavila po casu " << time << " minut"<< endl;
			
			continue;
		  }

		  // zapiranje handlov in polj. 
		  CloseHandle( explorer );
		  CloseHandle( pi.hProcess );
		  CloseHandle( pi.hThread );
	  }
  }

  delete[] dokumenti;
  delete[] cas;
  if (prog==false)
	  delete[] programi;
  log.close();
  stDokInPonov.close();
  lokacijeProgramov.close();
  Dokumenti.close();
  casiPikaza.close();

  cout  <<  "Konèano";
  cout << "izvajanje programa " << time << " minut = " << time/60 << " ur"<< endl;
  log << "izvajanje programa " << time << " minut = " << time/60 << " ur"<< endl;

  system("pause");
  return 0;
}


