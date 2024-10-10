using Microsoft.VisualStudio.Shell.Interop;
using Microsoft.VisualStudio;
using System.Net;
using System.ComponentModel.Design;

namespace NinginToolsExtension
{
    [Command(PackageIds.MyCommand)]
    internal sealed class MyCommand : BaseCommand<MyCommand>
    {
        protected override async Task ExecuteAsync(OleMenuCmdEventArgs e)
        {
            //Nothing
        }
    }
}
