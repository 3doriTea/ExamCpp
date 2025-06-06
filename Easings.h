#pragma once

class Ease
{
public:
	static inline float InBounce(float x)
	{
		return 1 - OutBounce(1 - x);
	}

	//  REF: https://easings.net/ja#easeOutBounce
	static inline float OutBounce(float x)
	{
		const float n1 = 7.5625f;
		const float d1 = 2.75f;

		if (x < 1.f / d1)
		{
			return n1 * x * x;
		}
		else if (x < 2.f / d1)
		{
			return n1 * (x -= 1.5f / d1) * x + 0.75f;
		}
		else if (x < 2.5f / d1)
		{
			return n1 * (x -= 2.25f / d1) * x + 0.9375f;
		}
		else
		{
			return n1 * (x -= 2.625f / d1) * x + 0.984375f;
		}
	}
	static inline float InOutBounce(float x)
	{
		return x < 0.5
			? (1 - OutBounce(1 - 2 * x)) / 2
			: (1 + OutBounce(2 * x - 1)) / 2;
	}
};
