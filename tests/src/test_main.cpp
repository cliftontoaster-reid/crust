/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:46:24 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/14 12:23:11 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUnit/Basic.h"
#include "../tests.hpp"

int main(void)
{
  if (CUE_SUCCESS != CU_initialize_registry())
  {
    return CU_get_error();
  }
  CU_basic_set_mode(CU_BRM_VERBOSE);

  run_img_tests();
  run_set_tests();
  run_scale_tests();

  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}
