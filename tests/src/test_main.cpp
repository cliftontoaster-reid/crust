/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:46:24 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/25 17:27:15 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUnit/Basic.h"
#include "../tests.hpp"

extern "C"
{
#include <mlx.h>
}

int main(void)
{
  if (CUE_SUCCESS != CU_initialize_registry())
  {
    return CU_get_error();
  }
  CU_basic_set_mode(CU_BRM_NORMAL);

  void *mlx = mlx_init();

  if (NULL == mlx)
  {
    printf("Error while initializing mlx\n");
    return 1;
  }

  run_img_tests();
  run_set_tests();
  run_scale_tests();
  run_camera_tests();

  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}
