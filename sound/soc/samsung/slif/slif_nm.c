/* sound/soc/samsung/vts/slif_nm.c
 *
 * ALSA SoC - Samsung VTS Serial Local Interface driver
 *
 * Copyright (c) 2019 Samsung Electronics Co. Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/clk.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_reserved_mem.h>
#include <linux/pm_runtime.h>
#include <linux/firmware.h>
#include <linux/dma-mapping.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/regmap.h>
#include <linux/sched/clock.h>
#include <linux/miscdevice.h>
#include <linux/pinctrl/consumer.h>

#include <asm-generic/delay.h>

#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/pcm_params.h>
#include <sound/tlv.h>
#include <sound/samsung/vts.h>

#include <sound/samsung/mailbox.h>
#include <sound/samsung/vts.h>
#include <soc/samsung/exynos-pmu-if.h>
#include <soc/samsung/exynos-el3_mon.h>

#define VTS_SOC_VERSION(m, n, r) (((m) << 16) | ((n) << 8) | (r))

#include "../vts/vts.h"
#if (VTS_SOC_VERSION(3, 0, 0) <= CONFIG_SND_SOC_SAMSUNG_VTS_VERSION)
#include "../vts/vts_soc_v3.h"
#elif (VTS_SOC_VERSION(2, 1, 0) <= CONFIG_SND_SOC_SAMSUNG_VTS_VERSION)
#include "../vts/vts_soc_v2_1.h"
#elif (VTS_SOC_VERSION(2, 0, 0) <= CONFIG_SND_SOC_SAMSUNG_VTS_VERSION)
#include "../vts/vts_soc_v2.h"
#elif (VTS_SOC_VERSION(1, 0, 0) <= CONFIG_SND_SOC_SAMSUNG_VTS_VERSION)
#include "../vts/vts_soc_v1.h"
#else
#include "vts_soc_v1.h"
#endif
#include "slif_util.h"
#include "slif_nm.h"

/* #define DEBUG */
void slif_dmic_aud_en(struct device *dev, int en)
{
	struct vts_data *data = dev_get_drvdata(dev);

	dev_info(dev, "%s en(%d)\n", __func__, en);
	dev_info(dev, "%s vts_state(%d)\n", __func__, data->vts_state);

	if (en) {
	} else {
	}
}

void slif_dmic_if_en(struct device *dev, int en)
{
	struct vts_data *data = dev_get_drvdata(dev);
	unsigned int enable_dmic_if = 0;

	dev_info(dev, "%s en(%d)\n", __func__, en);

	if (en) {
		enable_dmic_if = readl(data->sfr_base +
				VTS_DMIC_IF_ENABLE_DMIC_IF);
		writel((enable_dmic_if |
			(0x1 << VTS_DMIC_IF_ENABLE_DMIC_AUD0) |
			(0x1 << VTS_DMIC_IF_ENABLE_DMIC_AUD1) |
			(0x1 << VTS_DMIC_IF_ENABLE_DMIC_AUD2)),
			data->sfr_base + VTS_DMIC_IF_ENABLE_DMIC_IF);
	} else {
		enable_dmic_if = readl(data->sfr_base +
				VTS_DMIC_IF_ENABLE_DMIC_IF);
		writel(0x0, data->sfr_base + VTS_DMIC_IF_ENABLE_DMIC_IF);
	}
}
