This is a C port of John Barret's Perl script to change the Mayor/Organization
name in Simcity 2000.  Just for fun there's also a python script that will do
the same thing, if you'd prefer that for some reason.

Contents:

    ./bin
        ./bin/chmayor.exe
            The Windows version (win32), haven't tested but it should work
        ./bin/chmayor.x86
            Linux 32-bit version
        ./bin/chmayor.x86_64
            Linux 64-bit version

    ./src
        ./src/chmayor.c
            The source code for the C program
        ./src/chmayor.py
            The Python script that does the same thing

    ./misc
        The Makefiles for compilation, you probably won't need these


To use, copy the appropriate binary (chmayor.exe for Windows users) to the base
directory for your DOS Simcity 2000 install and run it.  It will look for the
'SC2000.DAT' file and alter it after you've entered the new information.


NOTE:   This assumes the DOS version of Simcity 2000.  If you're using the
        Windows 95 version, you can change the Mayor Name / Company Name from
        the windows registry editor.  Open regedit and navigate to
            HKEY_CURRENT_USER/Software/Maxis/SimCity 2000/Registration
        where you can edit the appropriate keys as you like.


Credits:
    Original version
        John Barret
        https://gist.github.com/jbarrett/5190597

    This version
        darseex@gmail.com

Feel free to spread this around, host it on your own site, etc.  In fact I would
prefer that, save me some bandwidth.
