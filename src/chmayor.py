#!/usr/bin/env python3
#===============================================================================
#   chmayor.py  |   version 1.0     |   github.com/jahendrie    |   2023-02-23
#
#   This is the python version of chmayor.c, which is itself a C port of John
#   Barret's perl script that changes the Mayor Name and Organization for
#   Simcity 2000.
#
#   Note:  This assumes the DOS version.  If you're using the Windows 95 version
#   then open up regedit and find
#       HKEY_CURRENT_USER/Software/Maxis/Simcity 2000/Registration
#   and edit the "Mayor Name" and "Company Name" keys to your heart's content.
#===============================================================================
import sys

def null_pad( obj, max_length ):
    for i in range( max_length - ( len( obj )) ):
        obj += b'\0'

    return( obj )


def print_help():
    print( '' )
    print("This script writes a new Mayor Name and Organization to SC2000.DAT,")
    print( "or whatever file you've passed to it, if you've renamed it." )
    print( '' )
    print("This assumes the DOS version of the game.  If you're using the win95")
    print("version, you'll have to open up the registry editor and navigate to")
    print( "\tHKEY_CURRENT_USER/Software/Maxis/SimCity 2000/Registration" )
    print( "and edit the 'Mayor Name' and 'Company Name' keys\n" )



def write_file( path, name, org ):
    with open( path, "rb+" ) as fin:
        fin.seek( 0x1E563D )
        fin.write( name )
        fin.write( org )


def main():

    max_length = 32

    ##  Filename stuff
    path = "SC2000.DAT"
    if len( sys.argv ) >= 2:
        if sys.argv[1] == "--help" or sys.argv[1] == "-h":
            print_help()
            sys.exit( 0 )
        else:
            path = sys.argv[1]

    ##  Get the name and fix the bytes object
    name = bytes( input( "Mayor name: " )[: max_length - 1 ], "ascii" )
    name = null_pad( name, max_length )

    ##  Get the organization and fix the bytes object
    org = bytes( input( "Organization: ")[: max_length -1 ], "ascii" )
    org = null_pad( org, max_length )

    r = input( "\nProceed? [Y/n]: " )
    if r == '\n' or r == '' or r.lower() == 'y':
        write_file( path, name, org )
        print( "\nData written to '%s'" % path )
    else:
        print( "Oh, nevermind then." )



if __name__ == "__main__":
    main()
