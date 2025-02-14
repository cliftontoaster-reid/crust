/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:56:33 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/14 12:21:46 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUnit/Basic.h"

extern "C"
{
#include "img/set.h"
#include "mlx.h"
}

static char *path = (char *)"data/set.xpm";
static t_2d tile_size = {24, 24};
static void *mlx = mlx_init();

void test_set_from_xpm(void)
{

  t_set *set = crust_set_from_xpm(mlx, path, tile_size);

  CU_ASSERT_PTR_NOT_NULL_FATAL(set);
  CU_ASSERT_PTR_NOT_NULL(set->mlx_ptr);
  CU_ASSERT_PTR_NOT_NULL(set->img);
  CU_ASSERT_EQUAL(set->tile_size.x, 24);
  CU_ASSERT_EQUAL(set->tile_size.y, 24);

  crust_set_drop(set);
}

void test_set_get_img(void)
{
  t_set *set = crust_set_from_xpm(mlx, path, tile_size);
  t_img *img = crust_set_get_img(set, 0);

  CU_ASSERT_PTR_NOT_NULL_FATAL(img);
  CU_ASSERT_PTR_NOT_NULL(img->mlx_ptr);
  CU_ASSERT_PTR_NOT_NULL(img->img_ptr);
  CU_ASSERT_EQUAL(img->width, 24);
  CU_ASSERT_EQUAL(img->height, 24);

  for (int y = 0; y < img->height; ++y)
  {
    for (int x = 0; x < img->width; ++x)
    {
      t_2d pos = {x, y};
      t_rgba pixel = crust_img_get_pixel(img, pos);
      t_rgba expected = crust_img_get_pixel(set->img, pos);

      CU_ASSERT_EQUAL(pixel.r, expected.r);
      CU_ASSERT_EQUAL(pixel.g, expected.g);
      CU_ASSERT_EQUAL(pixel.b, expected.b);
    }
  }

  crust_set_drop(set);
  crust_img_drop(img);
}

void test_set_get_img_off(void)
{
  t_set *set = crust_set_from_xpm(mlx, path, tile_size);
  t_img *img = crust_set_get_img(set, 1);

  CU_ASSERT_PTR_NOT_NULL_FATAL(img);
  CU_ASSERT_PTR_NOT_NULL(img->mlx_ptr);
  CU_ASSERT_PTR_NOT_NULL(img->img_ptr);
  CU_ASSERT_EQUAL(img->width, 24);
  CU_ASSERT_EQUAL(img->height, 24);

  for (int y = 0; y < img->height; ++y)
  {
    for (int x = 0; x < img->width; ++x)
    {
      t_2d pos = {x, y};
      t_rgba pixel = crust_img_get_pixel(img, pos);
      t_2d src_pos;
      src_pos.x = x + 24;
      src_pos.y = y;
      t_rgba expected = crust_img_get_pixel(set->img, src_pos);

      CU_ASSERT_EQUAL(pixel.r, expected.r);
      CU_ASSERT_EQUAL(pixel.g, expected.g);
      CU_ASSERT_EQUAL(pixel.b, expected.b);
    }
  }

  crust_set_drop(set);
  crust_img_drop(img);
}

void test_set_get_imgs(void)
{
  int start = 0;
  int end = 2;

  t_set *set = crust_set_from_xpm(mlx, path, tile_size);
  CU_ASSERT_PTR_NOT_NULL_FATAL(set);
  t_img *img = crust_set_get_imgs(set, start, end);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  for (int y = 0; y < img->height; ++y)
  {
    for (int x = 0; x < img->width; ++x)
    {
      t_2d pos = {x, y};
      t_rgba pixel = crust_img_get_pixel(img, pos);
      t_rgba expected = crust_img_get_pixel(set->img, pos);

      CU_ASSERT_EQUAL(pixel.r, expected.r);
      CU_ASSERT_EQUAL(pixel.g, expected.g);
      CU_ASSERT_EQUAL(pixel.b, expected.b);
    }
  }

  crust_set_drop(set);
  crust_img_drop(img);
}

void test_set_get_imgs_off(void)
{
  int start = 3;
  int end = 5;

  t_set *set = crust_set_from_xpm(mlx, path, tile_size);
  CU_ASSERT_PTR_NOT_NULL_FATAL(set);
  t_img *img = crust_set_get_imgs(set, start, end);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  t_2d base_pos;
  base_pos.x = 24 * 3;
  base_pos.y = 0;

  for (int y = 0; y < img->height; ++y)
  {
    for (int x = 0; x < img->width; ++x)
    {
      t_2d pos = {x, y};
      t_rgba pixel = crust_img_get_pixel(img, pos);
      t_2d src_pos;
      src_pos.x = x + base_pos.x;
      src_pos.y = y + base_pos.y;
      t_rgba expected = crust_img_get_pixel(set->img, src_pos);

      CU_ASSERT_EQUAL(pixel.r, expected.r);
      CU_ASSERT_EQUAL(pixel.g, expected.g);
      CU_ASSERT_EQUAL(pixel.b, expected.b);
    }
  }

  crust_set_drop(set);
  crust_img_drop(img);
}

void test_set_get_imgs_offy(void)
{
  int start = 12;
  int end = 14;

  t_set *set = crust_set_from_xpm(mlx, path, tile_size);
  CU_ASSERT_PTR_NOT_NULL_FATAL(set);
  t_img *img = crust_set_get_imgs(set, start, end);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  t_2d base_pos;
  base_pos.x = 0;
  base_pos.y = 24;

  for (int y = 0; y < img->height; ++y)
  {
    for (int x = 0; x < img->width; ++x)
    {
      t_2d pos = {x, y};
      t_rgba pixel = crust_img_get_pixel(img, pos);
      t_2d src_pos;
      src_pos.x = x + base_pos.x;
      src_pos.y = y + base_pos.y;
      t_rgba expected = crust_img_get_pixel(set->img, src_pos);

      CU_ASSERT_EQUAL(pixel.r, expected.r);
      CU_ASSERT_EQUAL(pixel.g, expected.g);
      CU_ASSERT_EQUAL(pixel.b, expected.b);
    }
  }

  crust_set_drop(set);
  crust_img_drop(img);
}

void test_get_imgs_by_pos(void)
{
  t_2d start;
  start.x = 0;
  start.y = 0;
  t_2d end;
  end.x = 2;
  end.y = 2;

  t_set *set = crust_set_from_xpm(mlx, path, tile_size);
  CU_ASSERT_PTR_NOT_NULL_FATAL(set);
  t_img *img = crust_set_get_imgs_by_pos(set, start, end);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  for (int y = 0; y < img->height; ++y)
  {
    for (int x = 0; x < img->width; ++x)
    {
      t_2d pos = {x, y};
      t_rgba pixel = crust_img_get_pixel(img, pos);
      t_rgba expected = crust_img_get_pixel(set->img, pos);

      CU_ASSERT_EQUAL(pixel.r, expected.r);
      CU_ASSERT_EQUAL(pixel.g, expected.g);
      CU_ASSERT_EQUAL(pixel.b, expected.b);
    }
  }

  crust_set_drop(set);
  crust_img_drop(img);
}

void test_get_imgs_by_pos_off(void)
{
  t_2d start;
  start.x = 3;
  start.y = 3;
  t_2d end;
  end.x = 5;
  end.y = 5;

  t_set *set = crust_set_from_xpm(mlx, path, tile_size);
  CU_ASSERT_PTR_NOT_NULL_FATAL(set);
  t_img *img = crust_set_get_imgs_by_pos(set, start, end);
  CU_ASSERT_PTR_NOT_NULL_FATAL(img);

  t_2d base_pos;
  base_pos.x = 24 * 3;
  base_pos.y = 24 * 3;

  for (int y = 0; y < img->height; ++y)
  {
    for (int x = 0; x < img->width; ++x)
    {
      t_2d pos = {x, y};
      t_rgba pixel = crust_img_get_pixel(img, pos);
      t_2d src_pos;
      src_pos.x = x + base_pos.x;
      src_pos.y = y + base_pos.y;
      t_rgba expected = crust_img_get_pixel(set->img, src_pos);

      CU_ASSERT_EQUAL(pixel.r, expected.r);
      CU_ASSERT_EQUAL(pixel.g, expected.g);
      CU_ASSERT_EQUAL(pixel.b, expected.b);
    }
  }

  crust_set_drop(set);
  crust_img_drop(img);
}

void run_set_tests(void)
{
  CU_pSuite suite = CU_add_suite("Set", NULL, NULL);

  CU_add_test(suite, "crust_set_from_xpm", test_set_from_xpm);
  CU_add_test(suite, "crust_set_get_img", test_set_get_img);
  CU_add_test(suite, "crust_set_get_img_off", test_set_get_img_off);
  CU_add_test(suite, "crust_set_get_imgs", test_set_get_imgs);
  CU_add_test(suite, "crust_set_get_imgs_off", test_set_get_imgs_off);
  CU_add_test(suite, "crust_set_get_imgs_offy", test_set_get_imgs_offy);
  CU_add_test(suite, "crust_set_get_imgs_by_pos", test_get_imgs_by_pos);
  CU_add_test(suite, "crust_set_get_imgs_by_pos_off", test_get_imgs_by_pos_off);
}