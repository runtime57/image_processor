#pragma once

#include <memory>
#include <string>
#include <vector>

#include "exceptions.h"
#include "filters/base.h"
#include "filters/blur.h"
#include "filters/crop.h"
#include "filters/crystallize.h"
#include "filters/edge.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharpening.h"
#include "parse.h"

std::shared_ptr<BaseFilter> CreateFilter(const FilterParams& filter_params);

std::vector<std::shared_ptr<BaseFilter>> CreateFilters(const std::vector<FilterParams>& filter_params);

void PrintDocumentation();

void ApplyFilters(const std::vector<std::shared_ptr<BaseFilter>>& filters, Image& image);