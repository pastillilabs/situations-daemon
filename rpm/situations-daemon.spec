# 
# Do NOT Edit the Auto-generated Part!
# Generated by: spectacle version 0.32
# 

Name:       situations-daemon

# >> macros
# << macros
%define __provides_exclude_from ^%{_datadir}/.*$
%define __requires_exclude ^libc|libgcc_s.*$

%{!?qtc_qmake:%define qtc_qmake %qmake}
%{!?qtc_qmake5:%define qtc_qmake5 %qmake5}
%{!?qtc_make:%define qtc_make make}
%{?qtc_builddir:%define _builddir %qtc_builddir}
Summary:    Background service launcher and plugins for Situations
Version:    1.0
Release:    0
Group:      Qt/Qt
License:    Copyright (C) Pastilli Labs - All Rights Reserved
URL:        http://www.pastillilabs.com
Source0:    %{name}-%{version}.tar.bz2
Source100:  situations-daemon.yaml
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  pkgconfig(Qt5Contacts)
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(contentaction5)
BuildRequires:  pkgconfig(KF5CalendarCore)
BuildRequires:  pkgconfig(libical)
BuildRequires:  pkgconfig(libmkcal-qt5)
Obsoletes:  situations-sonar

%description
Background Service and plugins for Situations


%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
# << build pre

%qtc_qmake5 

%qtc_make %{?_smp_mflags}

# >> build post
# << build post

%install
rm -rf %{buildroot}
# >> install pre
# << install pre
%qmake5_install

# >> install post
# << install post

%preun
# >> preun
%systemd_preun situations-daemon.service
# << preun

%post
/sbin/ldconfig
# >> post
%systemd_post situations-daemon.service
systemctl start situations-daemon
# << post

%postun
/sbin/ldconfig
# >> postun
%systemd_postun_with_restart situations-daemon.service
# << postun

%files
%defattr(-,root,root,-)
%{_datadir}/%{name}/lib/libcalendar.so
%{_datadir}/%{name}/lib/libcontacts.so
%{_datadir}/%{name}/lib/libdaemon.so
%{_datadir}/%{name}/lib/liblaunch.so
%{_sysconfdir}/systemd/system/situations-daemon.service
# >> files
# << files