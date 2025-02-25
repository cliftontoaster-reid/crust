/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:34 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/25 17:06:43 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUnit/Basic.h"

extern "C"
{
#include "map/camera.h"
#include <mlx.h>
}

void camera_init_test(void)
{
    t_2d pos = {0, 0};
    t_2d size = {100, 100};
    t_camera *camera = camera_init(pos, size);

    CU_ASSERT_PTR_NOT_NULL_FATAL(camera);
    CU_ASSERT_EQUAL(camera->pos.x, pos.x);
    CU_ASSERT_EQUAL(camera->pos.y, pos.y);
    CU_ASSERT_EQUAL(camera->size.x, size.x);
    CU_ASSERT_EQUAL(camera->size.y, size.y);
    camera_free(camera);
}

void camera_move_test(void)
{
    t_2d pos = {0, 0};
    t_2d size = {100, 100};
    t_camera *camera = camera_init(pos, size);

    t_2d move = {10, 10};
    camera_move(camera, move);

    CU_ASSERT_EQUAL(camera->pos.x, move.x);
    CU_ASSERT_EQUAL(camera->pos.y, move.y);
    
    camera_free(camera);
}

void camera_resize_test(void)
{
    t_2d pos = {0, 0};
    t_2d size = {100, 100};
    t_camera *camera = camera_init(pos, size);

    t_2d new_size = {200, 200};
    camera_resize(camera, new_size);

    CU_ASSERT_EQUAL(camera->size.x, new_size.x);
    CU_ASSERT_EQUAL(camera->size.y, new_size.y);
    camera_free(camera);
}

void camera_render_test(void)
{
    void *mlx = mlx_init();
    t_img *img = crust_img_from_xpm(mlx, (char *)"data/image.xpm");

    t_2d pos;
    // Center of the original image
    pos.x = img->width / 2;
    pos.y = img->height / 2;

    t_2d size;
    size.x = 100;
    size.y = 100;

    t_camera *camera = camera_init(pos, size);
    t_img *render = camera_render(camera, img, mlx);

    CU_ASSERT_PTR_NOT_NULL_FATAL(render);
    CU_ASSERT_EQUAL(render->width, 100);
    CU_ASSERT_EQUAL(render->height, 100);

    for (int y = 0; y < render->height; y++)
    {
        for (int x = 0; x < render->width; x++)
        {
            t_2d original;
            original.x = camera->pos.x - (camera->size.x / 2) + x;
            original.y = camera->pos.y - (camera->size.y / 2) + y;

            CU_ASSERT_FATAL(original.x >= 0);
            CU_ASSERT_FATAL(original.x < img->width);
            CU_ASSERT_FATAL(original.y >= 0);
            CU_ASSERT_FATAL(original.y < img->height);

            t_rgba original_pixel = crust_img_get_pixel(img, original);

            t_2d render_pos;
            render_pos.x = x;
            render_pos.y = y;
            t_rgba render_pixel = crust_img_get_pixel(render, render_pos);

            CU_ASSERT_EQUAL(original_pixel.r, render_pixel.r);
            CU_ASSERT_EQUAL(original_pixel.g, render_pixel.g);
            CU_ASSERT_EQUAL(original_pixel.b, render_pixel.b);
            CU_ASSERT_EQUAL(original_pixel.a, render_pixel.a);
        }
    }
    camera_free(camera);
    // Assume there is a function to free t_img if needed.
}

void camera_invalid_resize_test(void)
{
    t_2d pos = {0, 0};
    t_2d initial_size = {100, 100};
    t_camera *camera = camera_init(pos, initial_size);

    t_2d invalid_size = {0, 100}; // Zero x is invalid
    camera_resize(camera, invalid_size);
    // Size should remain unchanged
    CU_ASSERT_EQUAL(camera->size.x, initial_size.x);
    CU_ASSERT_EQUAL(camera->size.y, initial_size.y);

    invalid_size.x = 100;
    invalid_size.y = -50; // Negative height is invalid
    camera_resize(camera, invalid_size);
    CU_ASSERT_EQUAL(camera->size.x, initial_size.x);
    CU_ASSERT_EQUAL(camera->size.y, initial_size.y);

    camera_free(camera);
}

void camera_move_null_test(void)
{
    t_2d move = {50, 50};
    // Calling with NULL should do nothing without crashing.
    camera_move(NULL, move);
    CU_ASSERT_TRUE(1);
}

void camera_resize_null_test(void)
{
    t_2d new_size = {150, 150};
    // Calling with NULL should do nothing without crashing.
    camera_resize(NULL, new_size);
    CU_ASSERT_TRUE(1);
}

void camera_free_null_test(void)
{
    // Freeing a NULL camera should be safe.
    camera_free(NULL);
    CU_ASSERT_TRUE(1);
}

void run_camera_tests(void)
{
    CU_pSuite pSuite = CU_add_suite("Camera", NULL, NULL);

    CU_add_test(pSuite, "camera_init_test", camera_init_test);
    CU_add_test(pSuite, "camera_move_test", camera_move_test);
    CU_add_test(pSuite, "camera_resize_test", camera_resize_test);
    CU_add_test(pSuite, "camera_render_test", camera_render_test);
    CU_add_test(pSuite, "camera_invalid_resize_test", camera_invalid_resize_test);
    CU_add_test(pSuite, "camera_move_null_test", camera_move_null_test);
    CU_add_test(pSuite, "camera_resize_null_test", camera_resize_null_test);
    CU_add_test(pSuite, "camera_free_null_test", camera_free_null_test);
}