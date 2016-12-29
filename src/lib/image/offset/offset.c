/* 
 * Copyright (c) 2015-2016, Gregory M. Kurtzer. All rights reserved.
 * 
 * “Singularity” Copyright (c) 2016, The Regents of the University of California,
 * through Lawrence Berkeley National Laboratory (subject to receipt of any
 * required approvals from the U.S. Dept. of Energy).  All rights reserved.
 * 
 * This software is licensed under a customized 3-clause BSD license.  Please
 * consult LICENSE file distributed with the sources of this project regarding
 * your rights to use or distribute this software.
 * 
 * NOTICE.  This Software was developed under funding from the U.S. Department of
 * Energy and the U.S. Government consequently retains certain rights. As such,
 * the U.S. Government has been granted for itself and others acting on its
 * behalf a paid-up, nonexclusive, irrevocable, worldwide license in the Software
 * to reproduce, distribute copies to the public, prepare derivative works, and
 * perform publicly and display publicly, and to permit other to do so. 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h> 
#include <string.h>
#include <fcntl.h>  

#include "lib/message.h"
#include "util/util.h"
#include "util/file.h"

#include "../image.h"


int _singularity_image_offset(FILE *image_fp) {
    int ret = 0;
    int i = 0;

    if ( image_fp == NULL ) {
        singularity_message(ERROR, "Called singularity_image_offset() with NULL image pointer\n");
        ABORT(255);
    }

    singularity_message(VERBOSE, "Calculating image offset\n");
    rewind(image_fp);

    for (i=0; i < 64; i++) {
        int c = fgetc(image_fp); // Flawfinder: ignore
        if ( c == EOF ) {
            break;
        } else if ( c == '\n' ) {
            ret = i + 1;
            singularity_message(VERBOSE2, "Found image at an offset of %d bytes\n", ret);
            break;
        }
    }

    singularity_message(DEBUG, "Returning image_offset(image_fp) = %d\n", ret);

    return(ret);
}

