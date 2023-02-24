/*******************************************************************************
 *  chmayor.c   |   version 1.0     |   github.com/jahendrie    |   2023-02-23
 *
 *  Apparently there's no easy way to change the Mayor Name or Organization
 *  after setting the game up, so this is a program that will let you do that.
 *  If you don't give it an argument, it will open 'SC2000.DAT' in the current
 *  working directory; otherwise, it will accept whatever file you give it,
 *  though it expects SC2000.DAT and will probably just mess up whatever other
 *  file you give it.
 *
 *  Note:  This assumes the DOS version.  If you're using the Windows 95 version
 *  then open up regedit and find
 *      HKEY_CURRENT_USER/Software/Maxis/Simcity 2000/Registration
 *  and edit the "Mayor Name" and "Company Name" keys to your heart's content.
 *
 *  This is effectively a C port of John Barret's perl script:
 *  https://gist.github.com/jbarrett/5190597
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 32
#define PATH_SIZE 256

int write_file( FILE *fin, char *name, char *org )
{
    //  Org MUST be null-terminated so we're doing that here again just in case
    org[ (STRING_SIZE) - 1 ] = '\0';

    /*  Move to our offset in the file */
    fseek( fin, 0x1E563D, SEEK_SET );

    /*  Write the name */
    if( fwrite( name, sizeof( char ), (STRING_SIZE), fin ) == 0 )
        return( 1 );

    /*  Write the org */
    if( fwrite( org, sizeof( char ), (STRING_SIZE), fin ) == 0 )
        return( 1 );
    
    return( 0 );
}


int main( int argc, char *argv[] )
{
    /*  Default path and file pointer */
    char path[ 256 ];
    strncpy( path, "SC2000.DAT", (PATH_SIZE) );
    FILE *fin = NULL;

    /*  Two or more args, we just use the first as the file path */
    if( argc >= 2 )
    {
        /*  If they're asking for help, mostly just here for my dumb ass*/
        if(strncmp( argv[1], "-h", 2 ) == 0||strncmp( argv[1], "--help", 6)==0)
        {
            printf( "\nThis basic program will change the Mayor Name and ");
            printf( "Organization in\nSimcity 2000.  It assumes the data is ");
            printf( "stored in 'SC2000.DAT'.\n" );
            printf( "\nThis assumes the DOS version.  If you're " );
            printf( "using the Windows 95 version, then\nopen up regedit and ");
            printf( "find\n" );
            printf("\tHKEY_CURRENT_USER/Software/Maxis/SimCity 2000/Registration");
            printf( "\nand edit the 'Mayor Name' and 'Company Name' keys.\n\n");

            return( 0 );
        }

        else
            strncpy( path, argv[1], (PATH_SIZE) );
    }

    /*  Try to open the file */
    fin = fopen( path, "rb+" );
    if( fin == NULL )
    {
        fprintf( stderr, "ERROR:  Cannot read from '%s'\n", path );
        fprintf( stderr, "Aborting." );
        return( 1 );
    }

    /*  Let them know what the program does */
    printf("\nThis program will patch a given Mayor Name and Org. into\n");
    printf( "the SC2000.DAT file, overwriting the name/org currently there.\n");
    printf("\n-------------------------------------------------------------\n");
    printf( "MAKE A BACKUP OF THE 'SC2000.DAT' FILE BEFORE PROCEEDING!\n" );
    printf("-------------------------------------------------------------\n\n");

    /*  So far so good, lets make the buffers for the mayor and org names */
    char name[ (STRING_SIZE) ];
    char org[ (STRING_SIZE) ];

    /*  Null out both strings just for fun */
    for( int i = 0; i < (STRING_SIZE); ++i )
    { name[ i ] = '\0'; org[ i ] = '\0'; }

    /*  Get the name and trim off the newline */
    printf( "Mayor name: " );
    fgets( name, (STRING_SIZE), stdin );
    name[ strlen( name ) -1 ] = '\0';

    /*  Get the org and trim off the newline */
    printf( "Organization name: " );
    fgets( org, (STRING_SIZE), stdin );
    org[ strlen( org ) - 1 ] = '\0';

    /*  Prompt for confirmation */
    printf( "Proceed?  [Y/n]: " );
    char res = getchar();

    //  Write the file, or don't, whatever
    if( res == 'y' || res == 'Y' || res == '\n' )
    {
        if( write_file( fin, name, org ) == 0 )
            printf( "\nData written successfully.\n" );
        else
        {
            fprintf( stderr, "ERROR:  Unable to write data!\n" );
            fprintf( stderr, "Aborting.\n" );
            return( 1 );
        }
    }
    else
    {
        printf( "Very well, nevermind then.\n" );
        return( 0 );
    }

    //  Close the file
    fclose( fin );

    return( 0 );
}
