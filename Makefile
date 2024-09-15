# SPDX-FileCopyrightText: 2020 Efabless Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0

CARAVEL_ROOT?=$(PWD)/caravel
PRECHECK_ROOT?=${HOME}/mpw_precheck
SIM ?= RTL
CUP_ROOT?=$(PWD)
IP_ROOT?=$(PWD)/dependencies

SKYWATER_COMMIT=f70d8ca46961ff92719d8870a18a076370b85f6c
export OPEN_PDKS_COMMIT?=6d4d11780c40b20ee63cc98e645307a9bf2b2ab8
export PDK?=sky130A
export PDKPATH?=$(PDK_ROOT)/$(PDK)
# Install lite version of caravel, (1): caravel-lite, (0): caravel
CARAVEL_LITE?=1

MPW_TAG ?= 2024.09.12-1
export PDK_ROOT?=$(PWD)/dependencies/pdks

ifeq ($(CARAVEL_LITE),1)
	CARAVEL_NAME := caravel-lite
	CARAVEL_REPO := https://github.com/efabless/caravel-lite
	CARAVEL_TAG := $(MPW_TAG)
else
	CARAVEL_NAME := caravel
	CARAVEL_REPO := https://github.com/efabless/caravel
	CARAVEL_TAG := $(MPW_TAG)
endif

# Get IP blocks used in this test chip

# EFABLESS_URL=git@github.com:efabless
# OPENCIRCUITDESIGN_URL=git@github.com:RTimothyEdwards
EFABLESS_URL=https://github.com/efabless
OPENCIRCUITDESIGN_URL=https://github.com/RTimothyEdwards
# HSXO_IP=sky130_ht_ip__hsxo_cpz1
# COMPARATOR_IP=sky130_ak_ip__comparator
# LSXO_IP=sky130_be_ip__lsxo
# TEMPSENSOR_IP=sky130_od_ip__tempsensor
# HPOPAMP_IP=sky130_td_ip__opamp_hp
# OVERVOLTAGE_IP=sky130_vbl_ip__overvoltage
# BANDGAP_IP=sky130_cw_ip
# BROWNOUT_IP=sky130_ajc_ip__brownout
RCOSC16M_IP=sky130_ef_ip__rc_osc_16M
RCOSC500K_IP=sky130_ef_ip__rc_osc_500k
RHEOSTAT_IP=sky130_ef_ip__rheostat_8bit
BIASGEN_IP=sky130_ef_ip__biasgen
SWITCH_IP=sky130_ef_ip__analog_switches
POR_IP=sky130_sw_ip__bgrref_por
ULPCOMP_IP=sky130_icrg_ip__ulpcomp
MOSREF_IP=sky130_ak_ip__cmos_vref
LDO_IP=sky130_am_ip__ldo_01v8
SIGMADELTA_IP=sky130_iic_ip__audiodac_v1
RDAC_IP=sky130_ef_ip__rdac3v_8bit
CCOMP_IP=sky130_ef_ip__ccomp3v
SAMPLEHOLD_IP=sky130_ef_ip__samplehold
CDAC_IP=sky130_ef_ip__cdac3v_12bit
PLL_IP=sky130_aa_ip__programmable_pll

.PHONY: get_ip_blocks
get_ip_blocks: check_dependencies
	@if [ ! -d "$(IP_ROOT)/$(RCOSC500K_IP)" ]; then \
		echo "Creating $(RCOSC500K_IP) repository" ; \
		git clone --depth=1 \
			$(OPENCIRCUITDESIGN_URL)/$(RCOSC500K_IP) \
			$(IP_ROOT)/$(RCOSC500K_IP) ; \
	else \
		echo "Updating $(RCOSC500K_IP) repository" ; \
		( cd $(IP_ROOT)/$(RCOSC500K_IP) ; git pull ) ; \
	fi
	@if [ ! -d "$(IP_ROOT)/$(RCOSC16M_IP)" ]; then \
		echo "Creating $(RCOSC16M_IP) repository" ; \
		git clone --depth=1 \
			$(OPENCIRCUITDESIGN_URL)/$(RCOSC16M_IP) \
			$(IP_ROOT)/$(RCOSC16M_IP) ; \
	else \
		echo "Updat $(RCOSC16M_IP) repository" ; \
		( cd $(IP_ROOT)/$(RCOSC16M_IP) ; git pull ) ; \
	fi
	@if [ ! -d "$(IP_ROOT)/$(RHEOSTAT_IP)" ]; then \
		echo "Creating $(RHEOSTAT_IP) repository" ; \
		git clone --depth=1 \
			$(OPENCIRCUITDESIGN_URL)/$(RHEOSTAT_IP) \
			$(IP_ROOT)/$(RHEOSTAT_IP) ; \
	else \
		echo "Updating $(RHEOSTAT_IP) repository" ; \
		( cd $(IP_ROOT)/$(RHEOSTAT_IP) ; git pull ) ; \
	fi
	@if [ ! -d "$(IP_ROOT)/$(BIASGEN_IP)" ]; then \
		echo "Creating $(BIASGEN_IP) repository" ; \
		git clone --depth=1 \
			$(OPENCIRCUITDESIGN_URL)/$(BIASGEN_IP) \
			$(IP_ROOT)/$(BIASGEN_IP) ; \
	else \
		echo "Updating $(BIASGEN_IP) repository" ; \
		( cd $(IP_ROOT)/$(BIASGEN_IP) ; git pull ) ; \
	fi
	@if [ ! -d "$(IP_ROOT)/$(SWITCH_IP)" ]; then \
		echo "Creating $(SWITCH_IP) repository" ; \
		git clone --depth=1 \
			$(OPENCIRCUITDESIGN_URL)/$(SWITCH_IP) \
			$(IP_ROOT)/$(SWITCH_IP) ; \
	else \
		echo "Updating $(SWITCH_IP) repository" ; \
		( cd $(IP_ROOT)/$(SWITCH_IP) ; git pull ) ; \
	fi
	@if [ ! -d "$(IP_ROOT)/$(ULPCOMP_IP)" ]; then \
		echo "Creating $(ULPCOMP_IP) repository" ; \
		git clone --depth=1 --branch=tapeout_ci2406 \
			$(EFABLESS_URL)/$(ULPCOMP_IP) \
			$(IP_ROOT)/$(ULPCOMP_IP) ; \
	else \
		echo "Updating $(ULPCOMP_IP) repository" ; \
		( cd $(IP_ROOT)/$(ULPCOMP_IP) ; git pull ) ; \
	fi
	@if [ ! -d "$(IP_ROOT)/$(LDO_IP)" ]; then \
		echo "Creating $(LDO_IP) repository" ; \
		git clone --depth=1 --branch=tapeout_ci2406 \
			$(EFABLESS_URL)/$(LDO_IP) \
			$(IP_ROOT)/$(LDO_IP) ; \
	else \
		echo "Updating $(LDO_IP) repository" ; \
		( cd $(IP_ROOT)/$(LDO_IP) ; git pull ) ; \
	fi
	@if [ ! -d "$(IP_ROOT)/$(MOSREF_IP)" ]; then \
		echo "Creating $(MOSREF_IP) repository" ; \
		git clone --depth=1 --branch=tapeout_ci2406 \
			$(EFABLESS_URL)/$(MOSREF_IP) \
			$(IP_ROOT)/$(MOSREF_IP) ; \
	else \
		echo "Updating $(MOSREF_IP) repository" ; \
		( cd $(IP_ROOT)/$(MOSREF_IP) ; git pull ) ; \
	fi
	@if [ ! -d "$(IP_ROOT)/$(POR_IP)" ]; then \
		echo "Creating $(POR_IP) repository" ; \
		git clone --depth=1 --branch=tapeout_ci2406 \
			$(EFABLESS_URL)/$(POR_IP) \
			$(IP_ROOT)/$(POR_IP) ; \
	else \
		echo "Updating $(POR_IP) repository" ; \
		( cd $(IP_ROOT)/$(POR_IP) ; git pull ) ; \
	fi
	@if [ ! -d "$(IP_ROOT)/$(SIGMADELTA_IP)" ]; then \
		echo "Creating $(SIGMADELTA_IP) repository" ; \
		git clone --depth=1 --branch=tapeout_ci2406 \
			$(EFABLESS_URL)/$(SIGMADELTA_IP) \
			$(IP_ROOT)/$(SIGMADELTA_IP) ; \
	else \
		echo "Updating $(SIGMADELTA_IP) repository" ; \
		( cd $(IP_ROOT)/$(SIGMADELTA_IP) ; git pull ) ; \
	fi
	@if [ ! -d "$(IP_ROOT)/$(RDAC_IP)" ]; then \
		echo "Creating $(RDAC_IP) repository" ; \
		git clone --depth=1 \
			$(OPENCIRCUITDESIGN_URL)/$(RDAC_IP) \
			$(IP_ROOT)/$(RDAC_IP) ; \
	else \
		echo "Updating $(RDAC_IP) repository" ; \
		( cd $(IP_ROOT)/$(RDAC_IP) ; git pull ) ; \
	fi
	@if [ ! -d "$(IP_ROOT)/$(CCOMP_IP)" ]; then \
		echo "Creating $(CCOMP_IP) repository" ; \
		git clone --depth=1 --branch=tapeout_ci2406 \
			$(OPENCIRCUITDESIGN_URL)/$(CCOMP_IP) \
			$(IP_ROOT)/$(CCOMP_IP) ; \
	else \
		echo "Updating $(CCOMP_IP) repository" ; \
		( cd $(IP_ROOT)/$(CCOMP_IP) ; git pull ) ; \
	fi
	@if [ ! -d "$(IP_ROOT)/$(SAMPLEHOLD_IP)" ]; then \
		echo "Creating $(SAMPLEHOLD_IP) repository" ; \
		git clone --depth=1 \
			$(OPENCIRCUITDESIGN_URL)/$(SAMPLEHOLD_IP) \
			$(IP_ROOT)/$(SAMPLEHOLD_IP) ; \
	else \
		echo "Updating $(SAMPLEHOLD_IP) repository" ; \
		( cd $(IP_ROOT)/$(SAMPLEHOLD_IP) ; git pull ) ; \
	fi
	@if [ ! -d "$(IP_ROOT)/$(CDAC_IP)" ]; then \
		echo "Creating $(CDAC_IP) repository" ; \
		git clone --depth=1 \
			$(OPENCIRCUITDESIGN_URL)/$(CDAC_IP) \
			$(IP_ROOT)/$(CDAC_IP) ; \
	else \
		echo "Updating $(CDAC_IP) repository" ; \
		( cd $(IP_ROOT)/$(CDAC_IP) ; git pull ) ; \
	fi
	@if [ ! -d "$(IP_ROOT)/$(PLL_IP)" ]; then \
		echo "Creating $(PLL_IP) repository" ; \
		git clone --depth=1 \
			$(EFABLESS_URL)/$(PLL_IP) \
			$(IP_ROOT)/$(PLL_IP) ; \
	else \
		echo "Updating $(PLL_IP) repository" ; \
		( cd $(IP_ROOT)/$(PLL_IP) ; git pull ) ; \
	fi

# Include Caravel Makefile Targets
.PHONY: % : check-caravel
%: 
	export CARAVEL_ROOT=$(CARAVEL_ROOT) && $(MAKE) -f $(CARAVEL_ROOT)/Makefile $@

# Verify Target for running simulations
.PHONY: verify
verify:
	cd ./verilog/dv/ && \
	export SIM=${SIM} && \
		$(MAKE) -j$(THREADS)

# Install DV setup
.PHONY: simenv
simenv:
	docker pull efabless/dv_setup:latest

PATTERNS=$(shell cd verilog/dv && find * -maxdepth 0 -type d)
DV_PATTERNS = $(foreach dv, $(PATTERNS), verify-$(dv))
TARGET_PATH=$(shell pwd)
VERIFY_COMMAND="cd ${TARGET_PATH}/verilog/dv/$* && export SIM=${SIM} && make"
$(DV_PATTERNS): verify-% : ./verilog/dv/% 
	docker run -v ${TARGET_PATH}:${TARGET_PATH} -v ${PDK_ROOT}:${PDK_ROOT} \
                -v ${CARAVEL_ROOT}:${CARAVEL_ROOT} \
                -e TARGET_PATH=${TARGET_PATH} -e PDK_ROOT=${PDK_ROOT} \
                -e CARAVEL_ROOT=${CARAVEL_ROOT} \
                -u $(id -u $$USER):$(id -g $$USER) efabless/dv_setup:latest \
                sh -c $(VERIFY_COMMAND)
				
# Openlane Makefile Targets
BLOCKS = $(shell cd openlane && find * -maxdepth 0 -type d)
.PHONY: $(BLOCKS)
$(BLOCKS): %:
	cd openlane && $(MAKE) $*

.PHONY: setup
setup: check_dependencies install check-env install_mcw pdk-with-volare setup-timing-scripts setup-cocotb

# Install caravel
.PHONY: install
install:
	@echo "Installing $(CARAVEL_NAME).."
	@git clone -b $(CARAVEL_TAG) $(CARAVEL_REPO) $(CARAVEL_ROOT)

# Create symbolic links to caravel's main files
.PHONY: simlink
simlink: check-caravel
### Symbolic links relative path to $CARAVEL_ROOT 
	$(eval MAKEFILE_PATH := $(shell realpath --relative-to=openlane $(CARAVEL_ROOT)/openlane/Makefile))
	mkdir -p openlane
	cd openlane &&\
	ln -sf $(MAKEFILE_PATH) Makefile

BLOCKS = $(shell cd lvs && find * -maxdepth 0 -type d)
LVS_BLOCKS = $(foreach block, $(BLOCKS), lvs-$(block))
$(LVS_BLOCKS): lvs-% : ./lvs/%/lvs_config.json uncompress check-pdk check-precheck
	@$(eval INPUT_DIRECTORY := $(shell pwd))
	@cd $(PRECHECK_ROOT) && \
	docker run -v $(PRECHECK_ROOT):$(PRECHECK_ROOT) \
	-v $(INPUT_DIRECTORY):$(INPUT_DIRECTORY) \
	-v $(PDK_ROOT):$(PDK_ROOT) \
	-u $(shell id -u $(USER)):$(shell id -g $(USER)) \
	efabless/mpw_precheck:latest bash -c "cd $(PRECHECK_ROOT) ; python3 checks/lvs_check/lvs.py --pdk_path $(PDK_ROOT)/$(PDK) --design_directory $(INPUT_DIRECTORY) --output_directory $(INPUT_DIRECTORY)/lvs --design_name $* --config_file $(INPUT_DIRECTORY)/lvs/$*/lvs_config.json"

# Update Caravel
.PHONY: update_caravel
update_caravel: check-caravel
	cd $(CARAVEL_ROOT)/ && git checkout $(CARAVEL_TAG) && git pull

# Uninstall Caravel
.PHONY: uninstall
uninstall: 
	rm -rf $(CARAVEL_ROOT)

# Install Openlane
.PHONY: openlane
openlane: 
	cd openlane && $(MAKE) openlane

# Install Pre-check
# Default installs to the user home directory, override by "export PRECHECK_ROOT=<precheck-installation-path>"
.PHONY: precheck
precheck:
	@git clone --depth=1 --branch $(MPW_TAG) https://github.com/efabless/mpw_precheck.git $(PRECHECK_ROOT)
	@docker pull efabless/mpw_precheck:latest

.PHONY: run-precheck
run-precheck: check-pdk check-precheck
	@if [ "$$DISABLE_LVS" = "1" ]; then\
		$(eval INPUT_DIRECTORY := $(shell pwd)) \
		cd $(PRECHECK_ROOT) && \
		docker run -v $(PRECHECK_ROOT):$(PRECHECK_ROOT) \
		-v $(INPUT_DIRECTORY):$(INPUT_DIRECTORY) \
		-v $(PDK_ROOT):$(PDK_ROOT) \
		-e INPUT_DIRECTORY=$(INPUT_DIRECTORY) \
		-e PDK_PATH=$(PDK_ROOT)/$(PDK) \
		-e PDK_ROOT=$(PDK_ROOT) \
		-e PDKPATH=$(PDKPATH) \
		-u $(shell id -u $(USER)):$(shell id -g $(USER)) \
		efabless/mpw_precheck:latest bash -c "cd $(PRECHECK_ROOT) ; python3 mpw_precheck.py --input_directory $(INPUT_DIRECTORY) --pdk_path $(PDK_ROOT)/$(PDK) license makefile default documentation consistency gpio_defines xor magic_drc klayout_feol klayout_beol klayout_offgrid klayout_met_min_ca_density klayout_pin_label_purposes_overlapping_drawing klayout_zeroarea"; \
	else \
		$(eval INPUT_DIRECTORY := $(shell pwd)) \
		cd $(PRECHECK_ROOT) && \
		docker run -v $(PRECHECK_ROOT):$(PRECHECK_ROOT) \
		-v $(INPUT_DIRECTORY):$(INPUT_DIRECTORY) \
		-v $(PDK_ROOT):$(PDK_ROOT) \
		-e INPUT_DIRECTORY=$(INPUT_DIRECTORY) \
		-e PDK_PATH=$(PDK_ROOT)/$(PDK) \
		-e PDK_ROOT=$(PDK_ROOT) \
		-e PDKPATH=$(PDKPATH) \
		-u $(shell id -u $(USER)):$(shell id -g $(USER)) \
		efabless/mpw_precheck:latest bash -c "cd $(PRECHECK_ROOT) ; python3 mpw_precheck.py --input_directory $(INPUT_DIRECTORY) --pdk_path $(PDK_ROOT)/$(PDK)"; \
	fi

# Clean 
.PHONY: clean
clean:
	cd ./verilog/dv/ && \
		$(MAKE) -j$(THREADS) clean

check-caravel:
	@if [ ! -d "$(CARAVEL_ROOT)" ]; then \
		echo "Caravel Root: "$(CARAVEL_ROOT)" doesn't exists, please export the correct path before running make. "; \
		exit 1; \
	fi

check-precheck:
	@if [ ! -d "$(PRECHECK_ROOT)" ]; then \
		echo "Pre-check Root: "$(PRECHECK_ROOT)" doesn't exists, please export the correct path before running make. "; \
		exit 1; \
	fi

check-pdk:
	@if [ ! -d "$(PDK_ROOT)" ]; then \
		echo "PDK Root: "$(PDK_ROOT)" doesn't exists, please export the correct path before running make. "; \
		exit 1; \
	fi

.PHONY: help
help:
	cd $(CARAVEL_ROOT) && $(MAKE) help 
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$'

.PHONY: check_dependencies
check_dependencies:
	@if [ ! -d "$(PWD)/dependencies" ]; then \
		mkdir $(PWD)/dependencies; \
	fi

.PHONY: setup-timing-scripts
setup-timing-scripts: $(TIMING_ROOT)
	@( cd $(TIMING_ROOT) && git pull )
	@#( cd $(TIMING_ROOT) && git fetch && git checkout $(MPW_TAG); )

.PHONY: setup-cocotb
setup-cocotb: 
	@pip install caravel-cocotb==1.0.0 
	@(python3 $(PROJECT_ROOT)/verilog/dv/setup-cocotb.py $(CARAVEL_ROOT) $(MCW_ROOT) $(PDK_ROOT) $(PDK) $(PROJECT_ROOT))
	@docker pull efabless/dv:latest
	@docker pull efabless/dv:cocotb
