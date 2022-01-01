#include "PhotonUtil.h"

float map(float value, float org_range_start, float org_range_end, float new_range_start, float new_range_end)
{
	return ((value - org_range_start) / (org_range_end - org_range_start)) *
		(new_range_end - new_range_start) + new_range_start;
}