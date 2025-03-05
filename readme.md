This is the latest stable version that currently works on my airsoft replica without any problems.

Development was stalled for a while because of a high speed motor that drew a ton of amps on start-up , frying some of my mosfets randomly . Low TPA motors (11 TPA in my case) are not advised for this ETU
for multiple reasons:

	-random failure of mosfet
	-if the battery doesn't have enough discharge rate the microcontroller will restart on trigger pull , voltage drop too big for LDO to work.

Even though there is a PMOS for active brake , i do not use it in my code for this version as i want to get a perfect NMOS only version first.
You can just ignore the parts linked to the active brake feature list of references:
	-R9,R7,R8
	-Q5,Q8

Diode for flywheel protection is not necessary , i personally don't use it because i haven't had time to test the diode with the new motor, old motor always made it go up in flames , 
had better chances of survival without it.
Serial communication for easier debugging doesn't work for now.