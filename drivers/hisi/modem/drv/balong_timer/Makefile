#gcov
ifeq ($(strip $(llt_gcov)),y)
GCOV_PROFILE := y
endif

-include $(srctree)/drivers/hisi/modem/config/product/$(OBB_PRODUCT_NAME)/$(OBB_MODEM_CUST_CONFIG_DIR)/config/balong_product_config.mk
ifeq ($(strip $(CFG_CONFIG_MODULE_TIMER)),YES)
	obj-y	+= timer_slice.o
	obj-y	+= hardtimer_arm.o
	obj-y	+= hardtimer_core.o
	obj-y	+= softtimer_balong.o
endif
	

