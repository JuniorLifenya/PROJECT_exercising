Junior, <xuv016@uib.no> 
xuv016

Hei der, som jeg forsto det skulle man sende melding om oppgaven man ville gjøre i phys291?  Jeg har nå laget en detaljert plan for oppgaven jeg skal gjøre. Den innebærer :
1) Starte med Anharmonisk Osc som [V(x)= 1/2 (mw^2)(x^2)+t(x^4)]:
-  Implementere Runge-Kutta metode og kjøre en eigen-solvers med varierende t i C++ .
-  Sammenligne med analytiske harmonic osc ( t=0  for eksempel ) 
-  Plotte eigenvalues vs t med bruk av TGraph eller TMultiGraph. 

2) Visualisere 3-4 eigenfunksjoner med bruk av Root's TCanvas og  TGraph:
- Root macros plot: Spectrum ( E_n vs t ) , psi og prob density. 
- Utvide til 2 coupled harmonic Osc ( altså inkludere kx1x2).

3) Phase-space Analysis:
- Compute Wigner distrb for valgte eigentilstander/ superposisjoner.
- Generere quantum Poincare sections for å identifisere signaturer av nonlinear osc se mulig på chaos vs vanlige områder. 

4) Integrering / Automatisering i Root:
- Utvikle en root GUI/Script som :
Tar input for potential og coupling parametere. 
Kjører eigen-solver og phase-space styrke.
Automatisk lager figurer/ plotter også.
Jeg innser nå at oppgaven ble litt for stor og ambisiøst, men det er fordi jeg skal starte å skrive master-oppgave neste semester( phys339) og vil bruke dette her for å få en god start. 

Så prosjektet mitt er motivert av master-oppgaven og phys203 som jeg hadde forrige semester. Dette var et vanskelig fag om teoretisk mekanikk , og i faget måtte jeg se på bifurcation, chaos,  continuouse mekanikk, hamiltonian og lagrangian mekanikk. Beklager for en lang melding, men jeg har lyst til å starte med engang og bli ferdig så fort som mulig. 