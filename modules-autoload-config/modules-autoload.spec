Name: modules-autoload-config
Version: 1.0
Release: r0
Summary: Autoloading of dlkms during bootup
BuildArch: noarch
License: BSD-3-Clause-Clear
Source0: %{name}-%{version}.tar.gz

BuildRequires: systemd-rpm-macros

%description
Adding conf file to Autoload DLKMs during bootup.

%prep
%setup -qn %{name}

%install
mkdir -p  %{buildroot}%{_modulesloaddir}
mkdir -p  %{buildroot}%{_modprobedir}
cp i2cdev.conf "%{buildroot}%{_modulesloaddir}"
echo "options vfio_platform reset_required=0" > "%{buildroot}%{_modprobedir}/vfio.conf"
echo "vfio_platform" > "%{buildroot}%{_modulesloaddir}/vfio.conf"
echo "kryo_arm64_edac" > "%{buildroot}%{_modulesloaddir}/edac.conf"
echo "kiumd_kgsl" > "%{buildroot}%{_modulesloaddir}/kgsl.conf"

%files
%{_modulesloaddir}/i2cdev.conf
%{_modulesloaddir}/vfio.conf
%{_modprobedir}/vfio.conf
%{_modulesloaddir}/edac.conf
%{_modulesloaddir}/kgsl.conf
