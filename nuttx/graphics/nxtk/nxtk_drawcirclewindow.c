/****************************************************************************
 * graphics/nxtk/nxtk_drawcirclewindow.c
 *
 *   Copyright (C) 2011 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <spudmonkey@racsa.co.cr>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <debug.h>
#include <errno.h>

#include <nuttx/nx/nxglib.h>
#include <nuttx/nx/nxtk.h>

/****************************************************************************
 * Pre-Processor Definitions
 ****************************************************************************/
/* Named indices into the 16 circle points generated by nxgl_circlepts */

#define POINT_0p0      0 
#define POINT_22p5     1
#define POINT_45p0     2
#define POINT_67p5     3
#define POINT_90p0     4
#define POINT_112p5    5
#define POINT_135p0    6
#define POINT_157p5    7
#define POINT_180p0    8
#define POINT_202p5    9
#define POINT_225p0    10
#define POINT_247p5    11
#define POINT_270p0    12
#define POINT_292p5    13
#define POINT_315p0    14
#define POINT_337p5    15
#define NCIRCLE_POINTS 16

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: nxtk_drawcirclewindow
 *
 * Description:
 *  Draw a circular outline using the specified line thickness and color.
 *
 * Input Parameters:
 *   hfwnd  - The window handle returned by nxtk_openwindow()
 *   center - A pointer to the point that is the center of the circle
 *   radius - The radius of the circle in pixels.
 *   width  - The width of the line
 *   color  - The color to use to fill the line
 *
 * Return:
 *   OK on success; ERROR on failure with errno set appropriately
 *
 ****************************************************************************/

int nxtk_drawcirclewindow(NXTKWINDOW hfwnd, FAR const struct nxgl_point_s *center,
                          nxgl_coord_t radius, nxgl_coord_t width,
                          nxgl_mxpixel_t color[CONFIG_NX_NPLANES])
{
  struct nxgl_point_s pts[NCIRCLE_POINTS];
  FAR struct nxgl_vector_s vector;
  int i;
  int ret;

  /* Convert the circle to a set of 16 points */

  nxgl_circlepts(center, radius, pts);

  /* Draw each pair of points as a vector */

  for (i = POINT_0p0; i < POINT_337p5; i++)
    {
      vector.pt1.x = pts[i].x;
      vector.pt1.y = pts[i].y;
      vector.pt2.x = pts[i+1].x;
      vector.pt2.y = pts[i+1].y;
      ret = nxtk_drawlinewindow(hfwnd, &vector, width, color);
      if (ret != OK)
        {
          return ret;
        }
    }

  /* The final, closing vector is a special case */

  vector.pt1.x = pts[POINT_337p5].x;
  vector.pt1.y = pts[POINT_337p5].y;
  vector.pt2.x = pts[POINT_0p0].x;
  vector.pt2.y = pts[POINT_0p0].y;
  return nxtk_drawlinewindow(hfwnd, &vector, width, color);
}
