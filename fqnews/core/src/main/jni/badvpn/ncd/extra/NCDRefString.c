/**
 * @file NCDRefString.c
 * @author Ambroz Bizjak <ambrop7@gmail.com>
 * 
 * @section LICENSE
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "NCDRefString.h"

#include <misc/balloc.h>
#include <misc/offset.h>
#include <misc/debug.h>

static void ref_target_func_release (BRefTarget *ref_target)
{
    NCDRefString *o = UPPER_OBJECT(ref_target, NCDRefString, ref_target);
    BFree(o);
}

NCDRefString * NCDRefString_New (size_t size, char **out_buf)
{
    ASSERT(out_buf)
    
    bsize_t alloc_size = bsize_add(bsize_fromsize(sizeof(NCDRefString)), bsize_fromsize(size));
    NCDRefString *o = BAllocSize(alloc_size);
    if (!o) {
        return NULL;
    }
    BRefTarget_Init(&o->ref_target, ref_target_func_release);
    *out_buf = o->data;
    return o;
}

char const * NCDRefString_GetBuf (NCDRefString *o)
{
    return o->data;
}

BRefTarget * NCDRefString_RefTarget (NCDRefString *o)
{
    return &o->ref_target;
}
