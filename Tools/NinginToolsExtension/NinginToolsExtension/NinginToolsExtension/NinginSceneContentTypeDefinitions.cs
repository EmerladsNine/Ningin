using Microsoft.VisualStudio.Utilities;
using System.ComponentModel.Composition;

namespace NinginToolsExtension
{
    internal class NinginSceneContentTypeDefinitions
    {
        // Content Type Definition for NinginScene
        [Export(typeof(ContentTypeDefinition))]
        [Name("NinginScene")]
        [BaseDefinition("text")] // Base it on "text" since it's a text-based file format
        internal static ContentTypeDefinition NinginSceneContentType = null;

        // Associate the .ningin file extension with the NinginScene content type
        [Export(typeof(FileExtensionToContentTypeDefinition))]
        [ContentType("NinginScene")]
        [FileExtension(".ningin")] // The extension for your custom language
        internal static FileExtensionToContentTypeDefinition NinginSceneFileExtension = null;
    }
}
