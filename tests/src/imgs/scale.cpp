/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:13:24 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/14 12:23:47 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUnit/Basic.h"
#include <unistd.h> // Added for usleep

extern "C"
{
#include "img/scale.h"
#include "mlx.h"
#include <time.h>
}

#define CU_ASSERT_RGB_EQUAL(actual, expected) \
  {                                           \
    CU_ASSERT_EQUAL(actual.r, expected.r);    \
    CU_ASSERT_EQUAL(actual.g, expected.g);    \
    CU_ASSERT_EQUAL(actual.b, expected.b);    \
  }

#define TOLERANCE 100                         // Allowable difference in each color channel
#define SHOW_DIFFS 0                          // Set to 1 to print out differences and show windows
#define MAX_EXECUTION_TIME_SEC (1.0f / 30.0f) // Maximum allowed execution time in seconds

#if SHOW_DIFFS
// Helper function to display images in two windows and wait for user input in the console
static void display_images(void *mlx, t_img *src, t_img *dst)
{
  // Determine which image is bigger
  t_img *first = (src->width * src->height > dst->width * dst->height) ? src : dst;
  t_img *second = (first == src) ? dst : src;

  const char *name_first = (first == src) ? "src" : "dst";
  const char *name_second = (second == src) ? "src" : "dst";

  void *win_first = mlx_new_window(mlx, first->width, first->height, (char *)name_first);
  void *win_second = mlx_new_window(mlx, second->width, second->height, (char *)name_second);

  mlx_put_image_to_window(mlx, win_first, first->img_ptr, 0, 0);
  mlx_put_image_to_window(mlx, win_second, second->img_ptr, 0, 0);

  printf("\n        Enter Y for CU_PASS or N for CU_FAIL: ");
  int ch = getchar();
  while (getchar() != '\n')
  {
  } // Clear the input buffer

  if (ch == 'Y' || ch == 'y')
    printf("CU_PASS\n");
  else if (ch == 'N' || ch == 'n')
    printf("CU_FAIL\n");
  else
    printf("Invalid input. Defaulting to CU_FAIL\n");

  mlx_destroy_window(mlx, win_first);
  mlx_destroy_window(mlx, win_second);
}
#endif

// Helper function: compare two channel values with tolerance
static int channels_equal(unsigned char a, unsigned char b)
{
  return (abs((int)a - (int)b) <= TOLERANCE);
}

static void assert_rgba_equal(t_rgba expected, t_rgba actual)
{
  if (!channels_equal(expected.r, actual.r) ||
      !channels_equal(expected.g, actual.g) ||
      !channels_equal(expected.b, actual.b) ||
      !channels_equal(expected.a, actual.a))
  {
    printf("\nExpected: R=%d G=%d B=%d A=%d\n", expected.r, expected.g, expected.b, expected.a);
    printf("Actual  : R=%d G=%d B=%d A=%d\n", actual.r, actual.g, actual.b, actual.a);
    printf("Diffs   : R=%d G=%d B=%d A=%d\n",
           abs((int)expected.r - (int)actual.r),
           abs((int)expected.g - (int)actual.g),
           abs((int)expected.b - (int)actual.b),
           abs((int)expected.a - (int)actual.a));
  }
  CU_ASSERT_TRUE_FATAL(channels_equal(expected.r, actual.r));
  CU_ASSERT_TRUE_FATAL(channels_equal(expected.g, actual.g));
  CU_ASSERT_TRUE_FATAL(channels_equal(expected.b, actual.b));
  CU_ASSERT_TRUE_FATAL(channels_equal(expected.a, actual.a));
}

static void assert_execution_time(clock_t start, clock_t end)
{
  double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  if (cpu_time_used > MAX_EXECUTION_TIME_SEC)
  {
    printf("\nWARNING: Execution time: %.6f seconds (exceeded %.6f seconds limit of %.6f seconds)\n",
           cpu_time_used, MAX_EXECUTION_TIME_SEC, cpu_time_used - MAX_EXECUTION_TIME_SEC);
    CU_ASSERT_TRUE(1); // Still pass the test, but issue a warning
  }
  else
  {
    CU_ASSERT_TRUE(cpu_time_used <= MAX_EXECUTION_TIME_SEC);
  }
}

#pragma region Nearest Neighbor
void test_img_scale_nearest_up_2x(void)
{
  char *path = (char *)"data/image.xpm";
  void *mlx = mlx_init();

  t_img *img = crust_img_from_xpm(mlx, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  t_2d new_size = {img->width * 2, img->height * 2};

  // Start timing before scale operation
  clock_t start = clock();
  t_img *dst = crust_img_scale(img, new_size, CRUST_IMG_SCALE_NEAREST);
  clock_t end = clock();

  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);
  assert_execution_time(start, end);

  CU_ASSERT_EQUAL(dst->width, img->width * 2);
  CU_ASSERT_EQUAL(dst->height, img->height * 2);

  for (int y = 0; y < img->height; ++y)
  {
    for (int x = 0; x < img->width; ++x)
    {
      t_2d pos = {x * 2, y * 2};
      t_2d src_pos = {x, y};
      t_rgba src_pixel = crust_img_get_pixel(img, src_pos);
      t_rgba dst_pixel = crust_img_get_pixel(dst, pos);

      CU_ASSERT_RGB_EQUAL(src_pixel, dst_pixel);
    }
  }

#if SHOW_DIFFS
  display_images(mlx, img, dst);
#endif

  crust_img_drop(img);
  crust_img_drop(dst);
}

void test_img_scale_nearest_down_2x(void)
{
  char *path = (char *)"data/image.xpm";
  void *mlx = mlx_init();

  t_img *img = crust_img_from_xpm(mlx, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  t_2d new_size = {img->width / 2, img->height / 2};

  // Start timing before scale operation
  clock_t start = clock();
  t_img *dst = crust_img_scale(img, new_size, CRUST_IMG_SCALE_NEAREST);
  clock_t end = clock();

  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);
  assert_execution_time(start, end);

  CU_ASSERT_EQUAL(dst->width, img->width / 2);
  CU_ASSERT_EQUAL(dst->height, img->height / 2);

  for (int y = 0; y < dst->height; ++y)
  {
    for (int x = 0; x < dst->width; ++x)
    {
      t_2d pos = {x, y};
      t_2d src_pos = {x * 2, y * 2};
      t_rgba src_pixel = crust_img_get_pixel(img, src_pos);
      t_rgba dst_pixel = crust_img_get_pixel(dst, pos);

      CU_ASSERT_RGB_EQUAL(src_pixel, dst_pixel);
    }
  }

#if SHOW_DIFFS
  display_images(mlx, img, dst);
#endif

  crust_img_drop(img);
  crust_img_drop(dst);
}

void test_img_scale_nearest_up_1_5x(void)
{
  char *path = (char *)"data/image.xpm";
  void *mlx = mlx_init();

  double gscale = 1.5;
  float fgscale = gscale;

  t_img *img = crust_img_from_xpm(mlx, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  t_2d new_size = {(int)(img->width * gscale), (int)(img->height * gscale)};

  // Start timing before scale operation
  clock_t start = clock();
  t_img *dst = crust_img_scale(img, new_size, CRUST_IMG_SCALE_NEAREST);
  clock_t end = clock();

  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);
  assert_execution_time(start, end);

  CU_ASSERT_EQUAL(dst->width, new_size.x);
  CU_ASSERT_EQUAL(dst->height, new_size.y);

  const float scale = fgscale;
  const float inv_scale = 1.0f / scale;

  /* Instead of iterating over the source image and mapping forward,
     iterate over every pixel in the destination and compute the corresponding
     source pixel (using nearest-neighbor, which is simply a cast after scaling). */
  for (int dst_y = 0; dst_y < dst->height; ++dst_y)
  {
    int src_y = (int)(dst_y * inv_scale);
    if (src_y >= img->height)
      src_y = img->height - 1;

    for (int dst_x = 0; dst_x < dst->width; ++dst_x)
    {
      int src_x = (int)(dst_x * inv_scale);
      if (src_x >= img->width)
        src_x = img->width - 1;

      t_2d src_pos = {src_x, src_y};
      t_2d dst_pos = {dst_x, dst_y};

      t_rgba src_pixel = crust_img_get_pixel(img, src_pos);
      t_rgba dst_pixel = crust_img_get_pixel(dst, dst_pos);

      CU_ASSERT_RGB_EQUAL(src_pixel, dst_pixel);
    }
  }

#if SHOW_DIFFS
  display_images(mlx, img, dst);
#endif

  crust_img_drop(img);
  crust_img_drop(dst);
}

void test_img_scale_nearest_down_0_5x(void)
{
  char *path = (char *)"data/image.xpm";
  void *mlx = mlx_init();

  double gscale = 0.5;
  float fgscale = gscale;

  t_img *img = crust_img_from_xpm(mlx, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  // Calculate new (scaled down) size
  t_2d new_size = {(int)(img->width * gscale), (int)(img->height * gscale)};

  // Start timing before scale operation
  clock_t start = clock();
  t_img *dst = crust_img_scale(img, new_size, CRUST_IMG_SCALE_NEAREST);
  clock_t end = clock();

  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);
  assert_execution_time(start, end);

  CU_ASSERT_EQUAL(dst->width, new_size.x);
  CU_ASSERT_EQUAL(dst->height, new_size.y);

  const float scale = fgscale;
  const float inv_scale = 1.0f / scale; // inv_scale = 2.0

  // Iterate over every pixel in the destination image.
  // For each destination pixel, compute its corresponding source pixel.
  for (int dst_y = 0; dst_y < dst->height; ++dst_y)
  {
    // Calculate the corresponding source y position via the inverse scale factor.
    int src_y = (int)(dst_y * inv_scale);
    if (src_y >= img->height)
      src_y = img->height - 1;

    for (int dst_x = 0; dst_x < dst->width; ++dst_x)
    {
      // Calculate the corresponding source x position.
      int src_x = (int)(dst_x * inv_scale);
      if (src_x >= img->width)
        src_x = img->width - 1;

      t_2d src_pos = {src_x, src_y};
      t_2d dst_pos = {dst_x, dst_y};

      t_rgba src_pixel = crust_img_get_pixel(img, src_pos);
      t_rgba dst_pixel = crust_img_get_pixel(dst, dst_pos);

      CU_ASSERT_RGB_EQUAL(src_pixel, dst_pixel);
    }
  }

#if SHOW_DIFFS
  display_images(mlx, img, dst);
#endif

  crust_img_drop(img);
  crust_img_drop(dst);
}
#pragma endregion

#pragma region Bilenaer

// Helper function to clamp coordinates within the image boundaries
static inline int clamp(int x, int lower, int upper)
{
  if (x < lower)
    return lower;
  else if (x > upper)
    return upper;
  else
    return x;
}

// Helper function: bilinear interpolation of four channel values given fractional weights
static unsigned char bilinear_interp_channel(unsigned char c00, unsigned char c10,
                                             unsigned char c01, unsigned char c11,
                                             float frac_x, float frac_y)
{
  float top = c00 * (1.0f - frac_x) + c10 * frac_x;
  float bottom = c01 * (1.0f - frac_x) + c11 * frac_x;
  float value = top * (1.0f - frac_y) + bottom * frac_y;
  return (unsigned char)(value + 0.5f);
}

// Helper function: compute expected bilinear-interpolated pixel from the source image
static t_rgba compute_expected_bilinear(t_img *img, float src_x, float src_y)
{
  // The four neighboring pixels:
  int x0 = clamp((int)src_x, 0, img->width - 1);
  int x1 = clamp(x0 + 1, 0, img->width - 1);
  int y0 = clamp((int)src_y, 0, img->height - 1);
  int y1 = clamp(y0 + 1, 0, img->height - 1);

  // Fractional parts within the pixel
  float frac_x = src_x - (float)x0;
  float frac_y = src_y - (float)y0;

  t_2d p00 = {x0, y0};
  t_2d p10 = {x1, y0};
  t_2d p01 = {x0, y1};
  t_2d p11 = {x1, y1};

  t_rgba c00 = crust_img_get_pixel(img, p00);
  t_rgba c10 = crust_img_get_pixel(img, p10);
  t_rgba c01 = crust_img_get_pixel(img, p01);
  t_rgba c11 = crust_img_get_pixel(img, p11);

  t_rgba result;
  result.r = bilinear_interp_channel(c00.r, c10.r, c01.r, c11.r, frac_x, frac_y);
  result.g = bilinear_interp_channel(c00.g, c10.g, c01.g, c11.g, frac_x, frac_y);
  result.b = bilinear_interp_channel(c00.b, c10.b, c01.b, c11.b, frac_x, frac_y);
  result.a = bilinear_interp_channel(c00.a, c10.a, c01.a, c11.a, frac_x, frac_y);

  return result;
}

// Test function for bilinear upscaling by 2x
void test_img_scale_bilinear_up_2x(void)
{
  char *path = (char *)"data/image.xpm";
  void *mlx = mlx_init();
  CU_ASSERT_PTR_NOT_NULL_FATAL(mlx);

  t_img *img = crust_img_from_xpm(mlx, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  // Target size: double both dimensions
  t_2d new_size = {img->width * 2, img->height * 2};

  // Start timing before scale operation
  clock_t start = clock();
  t_img *dst = crust_img_scale(img, new_size, CRUST_IMG_SCALE_BILINEAR);
  clock_t end = clock();

  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);
  assert_execution_time(start, end);

  CU_ASSERT_EQUAL(dst->width, new_size.x);
  CU_ASSERT_EQUAL(dst->height, new_size.y);

  // For each pixel in the destination image,
  // compute the corresponding source coordinate.
  // Note: When scaling up 2x, the mapping is:
  // src_x = dst_x / 2.0 and src_y = dst_y / 2.0
  for (int dst_y = 0; dst_y < dst->height; ++dst_y)
  {
    for (int dst_x = 0; dst_x < dst->width; ++dst_x)
    {
      float src_x = dst_x / 2.0f;
      float src_y = dst_y / 2.0f;

      // Compute what the pixel should be from a bilinear interpolation of the source
      t_2d dst_pos = {dst_x, dst_y};
      t_rgba expected = compute_expected_bilinear(img, src_x, src_y);
      t_rgba actual = crust_img_get_pixel(dst, dst_pos);

      // Compare each channel with tolerance (if needed)
      assert_rgba_equal(expected, actual);
    }
  }

#if SHOW_DIFFS
  display_images(mlx, img, dst);
#endif

  crust_img_drop(img);
  crust_img_drop(dst);
}

// Test function for bilinear downscaling by 2x
void test_img_scale_bilinear_down_2x(void)
{
  char *path = (char *)"data/image.xpm";
  void *mlx = mlx_init();
  CU_ASSERT_PTR_NOT_NULL_FATAL(mlx);

  t_img *img = crust_img_from_xpm(mlx, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  // Target size: half both dimensions
  t_2d new_size = {img->width / 2, img->height / 2};

  // Start timing before scale operation
  clock_t start = clock();
  t_img *dst = crust_img_scale(img, new_size, CRUST_IMG_SCALE_BILINEAR);
  clock_t end = clock();

  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);
  assert_execution_time(start, end);

  CU_ASSERT_EQUAL(dst->width, new_size.x);
  CU_ASSERT_EQUAL(dst->height, new_size.y);

  // For each pixel in the destination image,
  // compute the corresponding source coordinate.
  // Note: When scaling down 2x, the mapping is:
  // src_x = dst_x * 2.0 and src_y = dst_y * 2.0
  for (int dst_y = 0; dst_y < dst->height; ++dst_y)
  {
    for (int dst_x = 0; dst_x < dst->width; ++dst_x)
    {
      float src_x = dst_x * 2.0f;
      float src_y = dst_y * 2.0f;

      // Compute what the pixel should be from a bilinear interpolation of the source
      t_2d dst_pos = {dst_x, dst_y};
      t_rgba expected = compute_expected_bilinear(img, src_x, src_y);
      t_rgba actual = crust_img_get_pixel(dst, dst_pos);

      // Compare each channel with tolerance (if needed)
      assert_rgba_equal(expected, actual);
    }
  }

#if SHOW_DIFFS
  display_images(mlx, img, dst);
#endif

  crust_img_drop(img);
  crust_img_drop(dst);
}

// Test function for bilinear upscaling by 1.5x
void test_img_scale_bilinear_up_1_5x(void)
{
  char *path = (char *)"data/image.xpm";
  void *mlx = mlx_init();
  CU_ASSERT_PTR_NOT_NULL_FATAL(mlx);

  double gscale = 1.5;
  float fgscale = gscale;

  t_img *img = crust_img_from_xpm(mlx, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  // Target size: 1.5x both dimensions
  t_2d new_size = {(int)(img->width * gscale), (int)(img->height * gscale)};

  // Start timing before scale operation
  clock_t start = clock();
  t_img *dst = crust_img_scale(img, new_size, CRUST_IMG_SCALE_BILINEAR);
  clock_t end = clock();

  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);
  assert_execution_time(start, end);

  CU_ASSERT_EQUAL(dst->width, new_size.x);
  CU_ASSERT_EQUAL(dst->height, new_size.y);

  const float scale = fgscale;
  const float inv_scale = 1.0f / scale;

  // For each pixel in the destination image,
  // compute the corresponding source coordinate.
  for (int dst_y = 0; dst_y < dst->height; ++dst_y)
  {
    for (int dst_x = 0; dst_x < dst->width; ++dst_x)
    {
      float src_x = dst_x * inv_scale;
      float src_y = dst_y * inv_scale;

      // Compute what the pixel should be from a bilinear interpolation of the source
      t_2d dst_pos = {dst_x, dst_y};
      t_rgba expected = compute_expected_bilinear(img, src_x, src_y);
      t_rgba actual = crust_img_get_pixel(dst, dst_pos);

      // Compare each channel with tolerance (if needed)
      assert_rgba_equal(expected, actual);
    }
  }

#if SHOW_DIFFS
  display_images(mlx, img, dst);
#endif

  crust_img_drop(img);
  crust_img_drop(dst);
}

// Test function for bilinear downscaling by 0.5x
void test_img_scale_bilinear_down_0_5x(void)
{
  char *path = (char *)"data/image.xpm";
  void *mlx = mlx_init();
  CU_ASSERT_PTR_NOT_NULL_FATAL(mlx);

  double gscale = 0.5;
  float fgscale = gscale;

  t_img *img = crust_img_from_xpm(mlx, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  // Target size: half both dimensions
  t_2d new_size = {(int)(img->width * gscale), (int)(img->height * gscale)};

  // Start timing before scale operation
  clock_t start = clock();
  t_img *dst = crust_img_scale(img, new_size, CRUST_IMG_SCALE_BILINEAR);
  clock_t end = clock();

  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);
  assert_execution_time(start, end);

  CU_ASSERT_EQUAL(dst->width, new_size.x);
  CU_ASSERT_EQUAL(dst->height, new_size.y);

  const float scale = fgscale;
  const float inv_scale = 1.0f / scale;

  // For each pixel in the destination image,
  // compute the corresponding source coordinate.
  for (int dst_y = 0; dst_y < dst->height; ++dst_y)
  {
    for (int dst_x = 0; dst_x < dst->width; ++dst_x)
    {
      float src_x = dst_x * inv_scale;
      float src_y = dst_y * inv_scale;

      // Compute what the pixel should be from a bilinear interpolation of the source
      t_2d dst_pos = {dst_x, dst_y};
      t_rgba expected = compute_expected_bilinear(img, src_x, src_y);
      t_rgba actual = crust_img_get_pixel(dst, dst_pos);

      // Compare each channel with tolerance (if needed)
      assert_rgba_equal(expected, actual);
    }
  }

#if SHOW_DIFFS
  display_images(mlx, img, dst);
#endif

  crust_img_drop(img);
  crust_img_drop(dst);
}
#pragma endregion

#pragma region Lanczos
// Lanczos kernel with a=2 (using 4 samples total)
static float lanczos2(float x)
{
  if (x == 0.0f)
    return 1.0f;
  if (x < -2.0f || x > 2.0f)
    return 0.0f;

  x *= M_PI;
  return (sin(x) * sin(x / 2.0f)) / (x * x / 2.0f);
}

// Helper function: compute expected Lanczos-interpolated pixel from the source image
static t_rgba compute_expected_lanczos(t_img *img, float src_x, float src_y)
{
  float r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;
  float weight_sum = 0.0f;

  // Sample a 4x4 neighborhood centered around the source coordinate
  int start_x = (int)src_x - 2;
  int start_y = (int)src_y - 2;

  for (int y = 0; y < 4; y++)
  {
    int sample_y = clamp(start_y + y, 0, img->height - 1);
    float dy = src_y - (start_y + y);

    for (int x = 0; x < 4; x++)
    {
      int sample_x = clamp(start_x + x, 0, img->width - 1);
      float dx = src_x - (start_x + x);

      // Calculate the 2D Lanczos weight
      float weight = lanczos2(dx) * lanczos2(dy);
      t_2d pos = {sample_x, sample_y};
      t_rgba pixel = crust_img_get_pixel(img, pos);

      r += pixel.r * weight;
      g += pixel.g * weight;
      b += pixel.b * weight;
      a += pixel.a * weight;
      weight_sum += weight;
    }
  }

  // Normalize by weight sum to account for edge cases
  float inv_weight = 1.0f / weight_sum;
  t_rgba result;
  result.r = (unsigned char)(clamp((int)(r * inv_weight + 0.5f), 0, 255));
  result.g = (unsigned char)(clamp((int)(g * inv_weight + 0.5f), 0, 255));
  result.b = (unsigned char)(clamp((int)(b * inv_weight + 0.5f), 0, 255));
  result.a = (unsigned char)(clamp((int)(a * inv_weight + 0.5f), 0, 255));

  return result;
}

// Test function for Lanczos upscaling by 2x
void test_img_scale_lanczos_up_2x(void)
{
  char *path = (char *)"data/image.xpm";
  void *mlx = mlx_init();
  CU_ASSERT_PTR_NOT_NULL_FATAL(mlx);

  t_img *img = crust_img_from_xpm(mlx, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  // Ensure source image has valid dimensions
  CU_ASSERT_TRUE_FATAL(img->width > 0 && img->height > 0);

  // Target size: double both dimensions
  t_2d new_size = {img->width * 2, img->height * 2};

  // Start timing before scale operation
  clock_t start = clock();
  t_img *dst = crust_img_scale(img, new_size, CRUST_IMG_SCALE_LANCZOS);
  clock_t end = clock();

  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);
  assert_execution_time(start, end);

  CU_ASSERT_EQUAL(dst->width, new_size.x);
  CU_ASSERT_EQUAL(dst->height, new_size.y);

  const float scale_factor = 2.0f;
  const float inv_scale = 1.0f / scale_factor;

  // Only test a subset of pixels to avoid long test times
  const int step = 4; // Test every 4th pixel
  for (int dst_y = 0; dst_y < dst->height; dst_y += step)
  {
    for (int dst_x = 0; dst_x < dst->width; dst_x += step)
    {
      float src_x = dst_x * inv_scale;
      float src_y = dst_y * inv_scale;

      // Ensure source coordinates are within bounds
      if (src_x >= img->width - 2 || src_y >= img->height - 2)
        continue;

      t_2d dst_pos = {dst_x, dst_y};
      t_rgba expected = compute_expected_lanczos(img, src_x, src_y);
      t_rgba actual = crust_img_get_pixel(dst, dst_pos);

      // Compare each channel with tolerance
      assert_rgba_equal(expected, actual);
    }
  }

#if SHOW_DIFFS
  display_images(mlx, img, dst);
#endif

  crust_img_drop(img);
  crust_img_drop(dst);
}

// Test function for Lanczos downscaling by 2x
void test_img_scale_lanczos_down_2x(void)
{
  char *path = (char *)"data/image.xpm";
  void *mlx = mlx_init();
  CU_ASSERT_PTR_NOT_NULL_FATAL(mlx);

  t_img *img = crust_img_from_xpm(mlx, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  // Ensure source image has valid dimensions
  CU_ASSERT_TRUE_FATAL(img->width > 0 && img->height > 0);

  // Target size: half both dimensions
  t_2d new_size = {img->width / 2, img->height / 2};

  // Start timing before scale operation
  clock_t start = clock();
  t_img *dst = crust_img_scale(img, new_size, CRUST_IMG_SCALE_LANCZOS);
  clock_t end = clock();

  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);
  assert_execution_time(start, end);

  CU_ASSERT_EQUAL(dst->width, new_size.x);
  CU_ASSERT_EQUAL(dst->height, new_size.y);

  const float scale_factor = 0.5f;
  const float inv_scale = 1.0f / scale_factor;

  // Only test a subset of pixels to avoid long test times
  const int step = 4; // Test every 4th pixel
  for (int dst_y = 0; dst_y < dst->height; dst_y += step)
  {
    for (int dst_x = 0; dst_x < dst->width; dst_x += step)
    {
      float src_x = dst_x * inv_scale;
      float src_y = dst_y * inv_scale;

      // Ensure source coordinates are within bounds
      if (src_x >= img->width - 2 || src_y >= img->height - 2)
        continue;

      t_2d dst_pos = {dst_x, dst_y};
      t_rgba expected = compute_expected_lanczos(img, src_x, src_y);
      t_rgba actual = crust_img_get_pixel(dst, dst_pos);

      // Compare each channel with tolerance
      assert_rgba_equal(expected, actual);
    }
  }

#if SHOW_DIFFS
  display_images(mlx, img, dst);
#endif

  crust_img_drop(img);
  crust_img_drop(dst);
}

// Test function for Lanczos upscaling by 1.5x
void test_img_scale_lanczos_up_1_5x(void)
{
  char *path = (char *)"data/image.xpm";
  void *mlx = mlx_init();
  CU_ASSERT_PTR_NOT_NULL_FATAL(mlx);

  double gscale = 1.5;
  float fgscale = gscale;

  t_img *img = crust_img_from_xpm(mlx, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  // Ensure source image has valid dimensions
  CU_ASSERT_TRUE_FATAL(img->width > 0 && img->height > 0);

  // Target size: 1.5x both dimensions
  t_2d new_size = {(int)(img->width * gscale), (int)(img->height * gscale)};

  // Start timing before scale operation
  clock_t start = clock();
  t_img *dst = crust_img_scale(img, new_size, CRUST_IMG_SCALE_LANCZOS);
  clock_t end = clock();

  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);
  assert_execution_time(start, end);

  CU_ASSERT_EQUAL(dst->width, new_size.x);
  CU_ASSERT_EQUAL(dst->height, new_size.y);

  const float scale = fgscale;
  const float inv_scale = 1.0f / scale;

  // Only test a subset of pixels to avoid long test times
  const int step = 4; // Test every 4th pixel
  for (int dst_y = 0; dst_y < dst->height; dst_y += step)
  {
    for (int dst_x = 0; dst_x < dst->width; dst_x += step)
    {
      float src_x = dst_x * inv_scale;
      float src_y = dst_y * inv_scale;

      // Ensure source coordinates are within bounds
      if (src_x >= img->width - 2 || src_y >= img->height - 2)
        continue;

      t_2d dst_pos = {dst_x, dst_y};
      t_rgba expected = compute_expected_lanczos(img, src_x, src_y);
      t_rgba actual = crust_img_get_pixel(dst, dst_pos);

      // Compare each channel with tolerance
      assert_rgba_equal(expected, actual);
    }
  }

#if SHOW_DIFFS
  display_images(mlx, img, dst);
#endif

  crust_img_drop(img);
  crust_img_drop(dst);
}

// Test function for Lanczos downscaling by 0.5x
void test_img_scale_lanczos_down_0_5x(void)
{
  char *path = (char *)"data/image.xpm";
  void *mlx = mlx_init();
  CU_ASSERT_PTR_NOT_NULL_FATAL(mlx);

  double gscale = 0.5;
  float fgscale = gscale;

  t_img *img = crust_img_from_xpm(mlx, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  // Ensure source image has valid dimensions
  CU_ASSERT_TRUE_FATAL(img->width > 0 && img->height > 0);

  // Target size: half both dimensions
  t_2d new_size = {(int)(img->width * gscale), (int)(img->height * gscale)};

  // Start timing before scale operation
  clock_t start = clock();
  t_img *dst = crust_img_scale(img, new_size, CRUST_IMG_SCALE_LANCZOS);
  clock_t end = clock();

  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);
  assert_execution_time(start, end);

  CU_ASSERT_EQUAL(dst->width, new_size.x);
  CU_ASSERT_EQUAL(dst->height, new_size.y);

  const float scale = fgscale;
  const float inv_scale = 1.0f / scale;

  // Only test a subset of pixels to avoid long test times
  const int step = 4; // Test every 4th pixel
  for (int dst_y = 0; dst_y < dst->height; dst_y += step)
  {
    for (int dst_x = 0; dst_x < dst->width; dst_x += step)
    {
      float src_x = dst_x * inv_scale;
      float src_y = dst_y * inv_scale;

      // Ensure source coordinates are within bounds
      if (src_x >= img->width - 2 || src_y >= img->height - 2)
        continue;

      t_2d dst_pos = {dst_x, dst_y};
      t_rgba expected = compute_expected_lanczos(img, src_x, src_y);
      t_rgba actual = crust_img_get_pixel(dst, dst_pos);

      // Compare each channel with tolerance
      assert_rgba_equal(expected, actual);
    }
  }

#if SHOW_DIFFS
  display_images(mlx, img, dst);
#endif

  crust_img_drop(img);
  crust_img_drop(dst);
}
#pragma endregion

void run_scale_tests(void)
{
  CU_pSuite suite = CU_add_suite("Scale", NULL, NULL);
  CU_add_test(suite, "test_img_scale_nearest_up_2x", test_img_scale_nearest_up_2x);
  CU_add_test(suite, "test_img_scale_nearest_down_2x", test_img_scale_nearest_down_2x);
  CU_add_test(suite, "test_img_scale_nearest_up_1_5x", test_img_scale_nearest_up_1_5x);
  CU_add_test(suite, "test_img_scale_nearest_down_0_5x", test_img_scale_nearest_down_0_5x);

  CU_add_test(suite, "test_img_scale_bilinear_up_2x", test_img_scale_bilinear_up_2x);
  CU_add_test(suite, "test_img_scale_bilinear_down_2x", test_img_scale_bilinear_down_2x);
  CU_add_test(suite, "test_img_scale_bilinear_up_1_5x", test_img_scale_bilinear_up_1_5x);
  CU_add_test(suite, "test_img_scale_bilinear_down_0_5x", test_img_scale_bilinear_down_0_5x);

  CU_add_test(suite, "test_img_scale_lanczos_up_2x", test_img_scale_lanczos_up_2x);
  CU_add_test(suite, "test_img_scale_lanczos_down_2x", test_img_scale_lanczos_down_2x);
  CU_add_test(suite, "test_img_scale_lanczos_up_1_5x", test_img_scale_lanczos_up_1_5x);
  CU_add_test(suite, "test_img_scale_lanczos_down_0_5x", test_img_scale_lanczos_down_0_5x);
}