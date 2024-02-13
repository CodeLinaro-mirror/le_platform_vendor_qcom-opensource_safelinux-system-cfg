# If kversion isn't defined on the rpmbuild line, define it here.
%{!?kversion: %define kversion %(uname -r)}

%define kmod_name oot-dtbo
%define debug_package %{nil}

Name: kernel-module-%{kmod_name}
Version: 1.0
Release:        1%{?dist}
Summary: External/out of tree device tree overlay.

License: GPLv2
Source0: %{name}-%{version}.tar.gz

BuildRequires: git
Requires: kernel-automotive-core-uname-r = %{kversion}

%description
For building device tree overlays for external modules.
Many kernel external modules are consuming their own device
stree structure, and expected to produce dtbo(device tree
overlay) files. These dtbo files are supposed to be overlayed
on mainline kernel device tree binary, based on certain
compatibility criteria.

%prep
%setup -qn %{name}

%build
make

%install
mkdir -p ${RPM_BUILD_ROOT}/lib/modules/%{kversion}/dtb/qcom/
cat %{_builddir}/%{name}/centos-stream-9/arch/arm64/boot/dts/qcom/sa8775p-ride.dtb.overlay \
            %{_builddir}/%{name}/sa8770p-ride/sa8770p-ride.dtb \
            %{_builddir}/%{name}/sa8775p-ride-mx/sa8775p-ride-mx.dtb \
            %{_builddir}/%{name}/sa8650p-ride/sa8650p-ride.dtb \
            %{_builddir}/%{name}/sa8255p-ride/sa8255p-ride.dtb \
            > ${RPM_BUILD_ROOT}/lib/modules/%{kversion}/dtb/qcom/sa8775p-ride.dtb.overlay
cp %{_builddir}/%{name}/sa8775p-qvp/sa8775p-qvp.dtb ${RPM_BUILD_ROOT}/lib/modules/%{kversion}/dtb/qcom/sa8775p-qvp.dtb

%files
/lib/modules/%{kversion}/dtb/qcom/sa8775p-ride.dtb.overlay
/lib/modules/%{kversion}/dtb/qcom/sa8775p-qvp.dtb

%changelog
* Tue Feb 13 2024 Jayanta Saren <quic_jsaren@quicinc.com> 1.0
- Add support for sa8775-qvp dtb
* Wed Dec 06 2023 Ninad Naik <quic_ninanaik@quicinc.com> 1.0
- Add support for sa8255p-ride dtb
* Fri Nov 24 2023 Ninad Naik <quic_ninanaik@quicinc.com> 1.0
- Add support for sa8650p-ride dtb
* Wed Nov 8 2023 Sankalp Negi <quic_snegi@quicinc.com> 1.0
- Add support for sa8775p-ride-mx dtb
* Thu Oct 12 2023 Ninad Naik <quic_ninanaik@quicinc.com> 1.0
- Added support for sa8775, sa8775 pcie ep and sa8770 appended dtbo
* Fri Jul 14 2023 Parikshit Pareek <quic_ppareek@quicinc.com> 1.0
- First commit!
- Added minidump support.
- Added scm support.
- Added kaslr offset support.
