## Demo project folder voor CLion of VSCode te gebruiken in combinatie met ATXmega256a3uen/of atmel328p 
## Benodigdheden
### Hardware
- ATXmega256a3U board
- Arduino Uno (optioneel)
- Windows/Linux of Apple PC)
## Software
### ondersteuning voor alle platforms(MAC, Linux, Windows)
- [VSCode](https://code.visualstudio.com/)
- [Git](https://github.com/git-guides/install-git)
- [CLion 2020.1+](https://jetbrains.com/clion)
- [AVR8 GNU Toolchain Windows](https://github.com/ZakKemble/avr-gcc-build/releases/download/v12.1.0-1/avr-gcc-12.1.0-x64-windows.zip)
- [AVR8 GNU Toolchain Linux](https://github.com/ZakKemble/avr-gcc-build/releases/download/v12.1.0-1/avr-gcc-12.1.0-x64-linux.tar.bz2)
- [AVR8 GNU Toolchain Mac](https://ports.macports.org/port/avr-gcc/)
- [avrdude](https://download.savannah.gnu.org/releases/avrdude/) of voor de Mac (https://ports.macports.org/port/avrdude/)
### alleen Windows 
- [MinGW](https://github.com/niXman/mingw-builds-binaries/releases/download/12.2.0-rt_v10-rev2/i686-12.2.0-release-posix-dwarf-msvcrt-rt_v10-rev2.7z)
Je hebt wel 7-zip (https://www.7-zip.org/) nodig om dit bestand uit te pakken

Windows:
- Maak een root (=basis) folder bijv c:\school
- Maak hierbinnen een folder 'gcc'
- Maak idem voor 'mingw'
- unzip de avr-gcc inhoud in de gcc folder
- unzip de mingw inhoud in de mingw folder
- pak avrdude uit in een willekeurige folder en kopieer avrdude.exe EN avrdude.conf naar de c:/school/gcc/bin folder

Pas de PATH parameter aan met het pad naar de mingw/bin folder

## Alle platforms:

ga in de root folder staan met een terminal of CMD (onder windows).
type in : 

git clone https://gitlab.techniek.hva.nl/microcontrollers-prototyping/xmega_voorbeelden_hva.git

Als je nog niet in gitlab bent ingelogd wordt hierom gevraagd.

Het voorbeeld project wordt nu  binnengehaald

Installeer VSCode en/of Clion op de gebruikelijke manier.

Installeer bij VSCode (de extensions CMAKE Tools en C/C++ [dat zijn er meerdere])

### Openen project
- Voor VSCode open de folder 'XMega_voorbeeldem_hva'
- Voor Clion open het bestand 'CMakeLists.txt' in de folder 'XMega_voorbeelden_hva'
- Blijf alles bij CLion of OK of yes ed aanklikken (dus niets veranderen).
- Nu ga je vrijwel zeker fouten onderin op het scherm zien. Dit klopt omdat we nog aan moeten geven waar de compiler staat.
- Open het bestand 'file_locations.cmake' 
- Zet de TOOLCHAIN_PATH naar de juiste locatie (bijv: C:/school/gcc/bin/)
- Je moet wel voorwaarts slashes '/' gebruiken. En ook niet vergeten er na de 'bin' nog eentje te zetten
- Voor de Mac en Linux gebruikers is deze regel nodig en moet je de eerdere laten beginnen met een # (commentaar) set(TOOLCHAIN_PATH "")
- het is is nu VSCode en/of CLion opnieuw opstarten. Nu moet hij als het goed is automatisch de juiste folders laden en kan je compileren

### CLion
- Als het goed is zie je bovenin een kleine hamer en daarnaast een lijst van targets. Als je op die lijst klikt zie je alle actieve targets
- Kies 'blink.elf' en klik op de hamer. Als alles werkt naar behoren zie je onderaan in messages dat .txt 586 bytes groot is. Dat deel werkt alvast.

### VSCode
- Bij VSCode krijg je helemaal onderin een blauwe balk met (bij de eerste keer) de tekst 'scan for kits'. Daar moet je op klikken en gaat VSCode kijken welke compilers hij kan vinden op jouw machine. Kies er maar een uit. Als het goed is maakt het verder niet uit welke omdat dat straks toch wordt verwezen naar de avr-gcc omgeving.
- Als alles goed gaat krijg iets naar rechts te zein [All Meta]. Als je daar op klikt krijg je alle zgn targets te zien. Kies blink.elf 
- klik op 'Build' op die onderste regel en je krijgt hetzelfde te zien als bij CLion

### XMega flashen
- Default is alles al ingesteld voor de XMega. Dus stel de XMega in om geflashed te worden en kies nu target blink.build en klik op de hamer of [build] afh. van CLion of VSCode
- Nu moet hij gaan flashen.

### Arduino UNO
- Omdat het kan is tevens de mogelijkheid gemaakt om arduino UNO bare metal projecten uit te voeren. Je maakt dus GEEN gebruik van de Arduino Libraries maar je gaat op dezelfde wijze programmeren als bij de ATXMega.
- In elke subproject is een file CMakeLists.txt. Die mag je lokaal aanpassen.
- open blink_UNO/CmakeLists.txt
- verbose op 1 zetten levert heel veel compilatie/link/flash output. Dit kan interessant zijn als er foutgen ontstaan
- MY_CPU op atmel328p zetten zorgt dat de compiler uitgaat van de chip op de arduino UNO
- MY_COMPORT op COM18 verwacht bij mij dat de UNO aan COM18 hangt. Dit is vrijwel zeker anders bij jou
- Er zit ook een voorbeeld in hoe dit bij de MAC gaat.
- De laatste regel (include ../generic.cmake) zeker laten zitten. Die zorgt ervoor dat alles werkt.
- Nu kan je compileren en flashen op de UNO

### Nieuw subproject
- maak een kopieer de hele folder example_assignment naar een nieuwe folder onder de root 'xmega_voorbeelden_hva' en geef de nieuwe folder een andere naam (rename)
- De meest eenvoudige manier is om projects_active.cmake aan te passen
- Herstart VSCode of CLion (net waar je mee bezig bent) en als het goed is is jouw nieuwe target toegevoegd.
- In het nieuwe voorbeeld is een programma example_assignment.c gemaakt. Die mag je gerust renamen. 
- Voor deze nieuwe omgeving maakt het niet meer uit wat de naam van jouw programma is.
- Wat wel van belang is, is dat er EENMAAL in EEN van de sourcefiles een main() functie staat.
- Ook het gebruik van subfolders (src, inc etc) zijn toegestaan. Er wordt automatisch gescand voor alle sources.
- Een randvoorwaarde is dat VSCode en CLion niet weten dat je een nieuw source hebt toegevoegd (immers zgn Makefiles zijn al aangemaakt). Evvt. VSCode of Clion opnieuw opstarten lost dat op. Er is uiteraard een betere manier maar niet voor deze tekst.
 
