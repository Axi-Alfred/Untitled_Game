Detta repository innehåller vårt grupprojekt i Unreal Engine. Här finns alla delar av spelet, inklusive gameplay-system, banor, assets och ljud.

Arbetsregler

Innan du börjar arbeta ska du alltid hämta den senaste versionen av projektet. Arbeta aldrig direkt i main-branchen. Varje person ska arbeta i sin egen branch för att undvika konflikter.

Gör commits ofta, men se till att dina meddelanden är tydliga och beskriver vad du har gjort. Undvik otydliga meddelanden som “fix” eller “update”.

Kontrollera alltid vilka filer du lägger till innan du committar. Kommunicera med gruppen innan du ändrar gemensamma filer, särskilt Unreal-assets som leveler eller Blueprints.

Undvik att två personer arbetar på samma asset samtidigt, eftersom Unreal-filer (.uasset och .umap) är svåra att slå ihop.

Main-branchen ska alltid vara stabil och spelbar.

Brancher

Main-branchen innehåller endast stabila versioner av projektet.

All utveckling sker i separata feature-brancher. Varje branch ska motsvara en specifik funktion eller uppgift.

Exempel på namn:
feature/alfred-combat
feature/robin-ai
feature/ui-system

Setup

Installera Git, Git LFS och rätt version av Unreal Engine.

Klona repositoryt till din dator och aktivera Git LFS så att stora Unreal-filer hanteras korrekt.

Arbetsflöde

Börja alltid med att hämta senaste versionen från main.

Skapa eller byt till din egen branch och gör ditt arbete där.

När du gjort ändringar, kontrollera vilka filer som ändrats och gör en commit med ett tydligt meddelande.

Pusha din branch till GitHub regelbundet.

När ditt arbete är klart skapar du en pull request och slår ihop den med main först när allt fungerar som det ska.

Uppdatera din branch

Om main har uppdaterats medan du arbetar ska du hämta de senaste ändringarna och slå ihop dem med din branch. Lös eventuella konflikter innan du fortsätter.

Merge-konflikter

Om en konflikt uppstår, ta det lugnt. Kontrollera vilka filer som berörs och var extra försiktig med Unreal-assets. Om du är osäker, prata med gruppen innan du gör något.

Viktigt att tänka på

Unreal skapar många filer som inte ska laddas upp, till exempel Binaries, Intermediate, Saved och DerivedDataCache.

Stora filer som .uasset och .umap hanteras via Git LFS.

Eftersom dessa filer inte går att slå ihop på ett enkelt sätt är det viktigt att kommunicera inom gruppen.

Grupp

Alfred Pereira
[Name]
[Name]
[Name]

Engine-version

Unreal Engine: [VERSION]

Sammanfattning

Hämta senaste versionen innan du börjar.
Arbeta i din egen branch.
Gör tydliga commits.
Pusha regelbundet.
Kommunicera med gruppen.
Håll main stabil.
