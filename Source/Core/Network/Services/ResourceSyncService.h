/*
    This file is part of Helio Workstation.

    Helio is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Helio is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helio. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "BackendService.h"
#include "RevisionsSyncThread.h"
#include "ProjectCloneThread.h"
#include "ProjectDeleteThread.h"
#include "UpdatesCheckThread.h"
#include "RequestResourceThread.h"

class ResourceSyncService final : private BackendService
{
public:

    ResourceSyncService(const ResourceManagerPool &rm);


    void fetchRevisionsInfo(WeakReference<VersionControl> vcs,
        const String &projectId, const String &projectName);


    void syncRevisions(WeakReference<VersionControl> vcs,
        const String &projectId, const String &projectName,
        const Array<String> &revisionIdsToSync);

    void cancelSyncRevisions();


    void cloneProject(WeakReference<VersionControl> vcs,
        const String &projectId);

    void cancelCloneProject();

    void deleteProject(const String &projectId);


private:

    ProjectCloneThread *prepareProjectCloneThread();
    ProjectDeleteThread *prepareProjectDeleteThread();

    RevisionsSyncThread *prepareSyncRevisionsThread();
    RevisionsSyncThread *prepareFetchRevisionsThread();

    UpdatesCheckThread *prepareUpdatesCheckThread();
    RequestResourceThread *prepareResourceRequestThread();

    ResourceManagerPool resourceManagers;
};
