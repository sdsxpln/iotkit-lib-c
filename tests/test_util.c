/*
 * Copyright (c) 2014 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../lib/cJSON/cJSON.h"
#include "../src/util.h"

bool checkResponseValue(char *response, int responseCode) {
    cJSON *json = NULL, *jitem = NULL;

// parse the file
    json = cJSON_Parse(response);
    if (!json) {
        fprintf(stderr,"Error before: [%s]\n",cJSON_GetErrorPtr());
        return false;
    } else {
        if (!isJsonObject(json)) {
            fprintf(stderr,"Invalid JSON format response\n");
            return false;
        }

        jitem = cJSON_GetObjectItem(json, "code");
        if (!isJsonNumber(jitem)) {
            fprintf(stderr,"Invalid JSON format for json property %s\n", jitem->string);
            return false;
        }

        if (jitem->valueint == responseCode) {
            return true;
        }
    }
}
