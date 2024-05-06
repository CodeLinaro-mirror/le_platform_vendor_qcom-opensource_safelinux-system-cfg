Name: modules-autoload-config
Version: 1.0
Release: r0
Summary: Autoloading of dlkms during bootup
BuildArch: noarch
License: BSD-3-Clause-Clear
Source0: %{name}-%{version}.tar.gz

BuildRequires: systemd-rpm-macros dracut

%description
Adding conf file to Autoload DLKMs during bootup.

%global dracut_modules_dir /usr/lib/dracut/modules.d
%global dracut_module_destdir %{dracut_modules_dir}/99qcom-kernel-modules

%prep
%setup -qn %{name}

%install
mkdir -p  %{buildroot}%{_modulesloaddir}
mkdir -p  %{buildroot}%{_modprobedir}
cp i2cdev.conf "%{buildroot}%{_modulesloaddir}"
cp spidev.conf "%{buildroot}%{_modulesloaddir}"
echo "options vfio_platform reset_required=0" > "%{buildroot}%{_modprobedir}/vfio.conf"
echo "vfio_platform" > "%{buildroot}%{_modulesloaddir}/vfio.conf"
echo "kryo_arm64_edac" > "%{buildroot}%{_modulesloaddir}/edac.conf"
echo "kiumd_kgsl" > "%{buildroot}%{_modulesloaddir}/kgsl.conf"
echo "uinput" > "%{buildroot}%{_modulesloaddir}/vmm_pwr_key.conf"
echo "dump_boot_log" > "%{buildroot}%{_modulesloaddir}/dump.conf"
echo "mhi_ep_net" > "%{buildroot}%{_modulesloaddir}/mhi_ep_net.conf"
echo "socinfo" > "%{buildroot}%{_modulesloaddir}/socinfo.conf"
echo "smem" > "%{buildroot}%{_modulesloaddir}/smem.conf"
echo "qcom_hwspinlock" > "%{buildroot}%{_modulesloaddir}/qcom_hwspinlock.conf"
mkdir -p %{buildroot}%{dracut_module_destdir}
install -DpZm 0644 dracut/module-setup.sh %{buildroot}%{dracut_module_destdir}

%files
%dir %{dracut_module_destdir}
%{dracut_module_destdir}/module-setup.sh
%{_modulesloaddir}/i2cdev.conf
%{_modulesloaddir}/spidev.conf
%{_modulesloaddir}/vfio.conf
%{_modprobedir}/vfio.conf
%{_modulesloaddir}/edac.conf
%{_modulesloaddir}/kgsl.conf
%{_modulesloaddir}/vmm_pwr_key.conf
%{_modulesloaddir}/dump.conf
%{_modulesloaddir}/mhi_ep_net.conf
%{_modulesloaddir}/socinfo.conf
%{_modulesloaddir}/smem.conf
%{_modulesloaddir}/qcom_hwspinlock.conf
