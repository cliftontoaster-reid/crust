/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:06:04 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/26 19:54:47 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUnit/Basic.h"

extern "C"
{
#include "img/img.h"
#include "mlx.h"
}

void test_crust_img_new(void)
{
  void *mlx = mlx_init();
  t_img *img = crust_img_new(mlx, 1024, 768);

  CU_ASSERT_PTR_NOT_NULL_FATAL(img);
  CU_ASSERT_PTR_NOT_NULL(img->mlx_ptr);
  CU_ASSERT_PTR_NOT_NULL(img->img_ptr);

  CU_ASSERT_EQUAL(img->width, 1024);
  CU_ASSERT_EQUAL(img->height, 768);

  crust_img_drop(img);
}

void test_crust_img_from_xpm(void)
{
  char *path = (char *)"data/image.xpm";
  void *owo = mlx_init();

  t_img *img = crust_img_from_xpm(owo, path);

  CU_ASSERT_PTR_NOT_NULL_FATAL(img);
  CU_ASSERT_PTR_NOT_NULL(img->mlx_ptr);
  CU_ASSERT_PTR_NULL(img->img_ptr);

  CU_ASSERT_EQUAL(img->width, 1024);
  CU_ASSERT_EQUAL(img->height, 768);

  crust_img_drop(img);
}

void test_img_put_pixel(void)
{
  void *mlx = mlx_init();
  t_img *img = crust_img_new(mlx, 3, 1);
  t_rgba color;
  color.r = 255;
  color.g = 0;
  color.b = 0;
  color.a = 0;
  t_2d pos = {1, 0};

  crust_img_put_pixel(img, pos, color);

  t_rgba pixel = crust_img_get_pixel(img, pos);

  CU_ASSERT_EQUAL(pixel.r, color.r);
  CU_ASSERT_EQUAL(pixel.g, color.g);
  CU_ASSERT_EQUAL(pixel.b, color.b);

  crust_img_drop(img);
}

void test_img_get_pixel(void)
{
  char *path = (char *)"data/image.xpm";
  void *owo = mlx_init();

  t_img *img = crust_img_from_xpm(owo, path);

  t_rgba expected_color;
  expected_color.r = 0x2B;
  expected_color.g = 0x4E;
  expected_color.b = 0x7E;

  for (int x = 0; x < 20; ++x)
  {
    t_2d pos = {x, 1};
    t_rgba pixel = crust_img_get_pixel(img, pos);

    CU_ASSERT_EQUAL(pixel.r, expected_color.r);
    CU_ASSERT_EQUAL(pixel.g, expected_color.g);
    CU_ASSERT_EQUAL(pixel.b, expected_color.b);
  }

  crust_img_drop(img);
}

void test_img_cpy_full(void)
{
  char *path = (char *)"data/image.xpm";
  void *owo = mlx_init();

  t_img *img = crust_img_from_xpm(owo, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  t_img *dst = crust_img_new(owo, img->width, img->height);
  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);

  t_2d pos = {0, 0};
  t_2d size = {img->width, img->height};
  crust_img_cpy(dst, img, pos, size);

  for (int y = 0; y < img->height; ++y)
  {
    for (int x = 0; x < img->width; ++x)
    {
      t_2d pos = {x, y};
      t_rgba src_pixel = crust_img_get_pixel(img, pos);
      t_rgba dst_pixel = crust_img_get_pixel(dst, pos);

      CU_ASSERT_EQUAL(src_pixel.r, dst_pixel.r);
      CU_ASSERT_EQUAL(src_pixel.g, dst_pixel.g);
      CU_ASSERT_EQUAL(src_pixel.b, dst_pixel.b);
    }
  }

  crust_img_drop(img);
  crust_img_drop(dst);
}

void test_img_cpy_partial(void)
{
  char *path = (char *)"data/image.xpm";
  void *owo = mlx_init();

  t_img *img = crust_img_from_xpm(owo, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  t_img *dst = crust_img_new(owo, img->width / 2, img->height / 2);
  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);

  t_2d pos = {0, 0};
  t_2d size = {img->width / 2, img->height / 2};
  crust_img_cpy(dst, img, pos, size);

  for (int y = 0; y < dst->height; ++y)
  {
    for (int x = 0; x < dst->width; ++x)
    {
      t_2d pos = {x, y};
      t_rgba src_pixel = crust_img_get_pixel(img, pos);
      t_rgba dst_pixel = crust_img_get_pixel(dst, pos);

      CU_ASSERT_EQUAL(src_pixel.r, dst_pixel.r);
      CU_ASSERT_EQUAL(src_pixel.g, dst_pixel.g);
      CU_ASSERT_EQUAL(src_pixel.b, dst_pixel.b);
    }
  }

  crust_img_drop(img);
  crust_img_drop(dst);
}

void test_img_crop(void)
{
  char *path = (char *)"data/image.xpm";
  void *owo = mlx_init();

  t_img *img = crust_img_from_xpm(owo, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  t_2d pos = {0, 0};
  t_2d size = {img->width / 2, img->height / 2};
  t_img *dst = crust_img_crop(img, pos, size);
  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);

  for (int y = 0; y < dst->height; ++y)
  {
    for (int x = 0; x < dst->width; ++x)
    {
      t_2d pos = {x, y};
      t_rgba src_pixel = crust_img_get_pixel(img, pos);
      t_rgba dst_pixel = crust_img_get_pixel(dst, pos);

      CU_ASSERT_EQUAL(src_pixel.r, dst_pixel.r);
      CU_ASSERT_EQUAL(src_pixel.g, dst_pixel.g);
      CU_ASSERT_EQUAL(src_pixel.b, dst_pixel.b);
    }
  }

  crust_img_drop(img);
  crust_img_drop(dst);
}

void test_img_crop_off(void)
{
  char *path = (char *)"data/image.xpm";
  void *owo = mlx_init();

  t_img *img = crust_img_from_xpm(owo, path);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  t_2d pos = {1, 0};    // offset position in source image
  t_2d size = {10, 10}; // size of cropped area
  t_img *dst = crust_img_crop(img, pos, size);
  CU_ASSERT_PTR_NOT_NULL_FATAL(dst);

  for (int y = 0; y < dst->height; ++y)
  {
    for (int x = 0; x < dst->width; ++x)
    {
      t_2d src_pos = {x + pos.x, y + pos.y};
      t_rgba src_pixel = crust_img_get_pixel(img, src_pos);
      t_2d dst_pos = {x, y};
      t_rgba dst_pixel = crust_img_get_pixel(dst, dst_pos);

      if (src_pixel.r != dst_pixel.r || src_pixel.g != dst_pixel.g || src_pixel.b != dst_pixel.b)
      {
        printf("Mismatch: expected (%d, %d, %d), got (%d, %d, %d) at pos (%d, %d) from (%d, %d)\n",
               src_pixel.r, src_pixel.g, src_pixel.b,
               dst_pixel.r, dst_pixel.g, dst_pixel.b,
               dst_pos.x, dst_pos.y,
               src_pos.x, src_pos.y);
      }

      CU_ASSERT_EQUAL(src_pixel.r, dst_pixel.r);
      CU_ASSERT_EQUAL(src_pixel.g, dst_pixel.g);
      CU_ASSERT_EQUAL(src_pixel.b, dst_pixel.b);
    }
  }

  crust_img_drop(img);
  crust_img_drop(dst);
}

void run_img_tests(void)
{
  CU_pSuite pSuite = CU_add_suite("Imgs", NULL, NULL);

  CU_add_test(pSuite, "crust_img_new", test_crust_img_new);
  CU_add_test(pSuite, "crust_img_from_xpm", test_crust_img_from_xpm);
  CU_add_test(pSuite, "crust_img_put_pixel", test_img_put_pixel);
  CU_add_test(pSuite, "crust_img_get_pixel", test_img_get_pixel);
  CU_add_test(pSuite, "crust_img_cpy_full", test_img_cpy_full);
  CU_add_test(pSuite, "crust_img_cpy_partial", test_img_cpy_partial);
  CU_add_test(pSuite, "crust_img_crop", test_img_crop);
  CU_add_test(pSuite, "crust_img_crop_off", test_img_crop_off);
}