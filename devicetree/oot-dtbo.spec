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
cp %{_builddir}/%{name}/centos-stream-9/arch/arm64/boot/dts/qcom/*.dtb.overlay \
	${RPM_BUILD_ROOT}/lib/modules/%{kversion}/dtb/qcom/

%files
/lib/modules/%{kversion}/dtb/qcom/sa8775p-ride.dtb.overlay

%changelog
* Fri Jul 14 2023 Parikshit Pareek <quic_ppareek@quicinc.com> 1.0
- First commit!
- Added minidump support.
- Added scm support.
- Added kaslr offset support.
