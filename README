@NerdLabs Productions Ltd.

Agapiou Marinos
Kamaras Georgios

This project is a very straight-forward team work. Most of the code was written with both members working in the same computer, simultaneously. If we could separate 
something, that would be these functions:
* finalscore() function is mostly a work of Georgios Kamaras
* undo() function and it's general implementation in the game is mostly a work of Marinos Agapiou
* fixedhandicap() and placefreehandicap() are mostly a work of Georgios Kamaras
* ko() and setfreehandicap() are mostly a work of Marinos Agapiou

From the various GTP commands, we implemented:
* protocol_version	* name		* version	* known_command		* list_commands		* quit		* boardsize
* clear_board		* komi		* play		* genmove		* showboard		* final_score	* undo
* fixed_handicap	* place_free_handicap		* set_free_handicap"

To compile the project, just type:
make
...and press <ENTER> :-)

To run the project:
Our command line arguments are expected to go as follows:

$ ./ipgo.cup -seed <seed_number> -jap -superko

./ipgo.cup part is necessary
-seed <seed_number> part is necessary
-jap part is optional
-superko part is optional

-------------------------------------------------------------------------

NOTE: For Go Cup version only:
-seed <seed_number> is still necessary, however we don't use randomality in the genmove's function, we still need it for the place_free_handicap's function,
					which in our program is still based in randomality. For the Go Cup, we tried (and achieved) to change out initial
					submit (for evaluation) as little as possible.
